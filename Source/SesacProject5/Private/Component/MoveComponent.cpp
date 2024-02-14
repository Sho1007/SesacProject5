// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/MoveComponent.h"

#include "EnhancedInputComponent.h"
#include "EntitySystem/MovieSceneComponentDebug.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	OwningCharacter = GetOwner<ACharacter>();
	check(OwningCharacter != nullptr && OwningCharacter->IsValidLowLevelFast());

	if (OwningCharacter->HasAuthority())
	{
		SetIsReplicated(true);
	}
}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMoveComponent::SetupPlayerInputComponent(UEnhancedInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &UMoveComponent::MoveAction);
	PlayerInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &UMoveComponent::LookAction);
	PlayerInputComponent->BindAction(IA_Crouch, ETriggerEvent::Started, this, &UMoveComponent::CrouchAction);
	PlayerInputComponent->BindAction(IA_Sprint, ETriggerEvent::Started, this, &UMoveComponent::SprintStartAction);
	PlayerInputComponent->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &UMoveComponent::SprintEndAction);
}

bool UMoveComponent::IsSprint() const
{
	return bIsSprint;
}

void UMoveComponent::MoveAction(const FInputActionValue& Value)
{
	// UE_LOG(LogTemp, Warning, TEXT("UMoveComponent::MoveAction"));

	FVector2D Vector2DValue = Value.Get<FVector2D>();

	if (Vector2DValue == FVector2D::ZeroVector) return;

	FRotationMatrix RotationMatrix(FRotator(0, OwningCharacter->GetControlRotation().Yaw, 0));

	// UE_LOG(LogTemp, Warning, TEXT("UMoveComponent::MoveAction) CurrentMoveSpeed : %f"), CurrentMoveSpeed);

	OwningCharacter->AddMovementInput(RotationMatrix.GetScaledAxis(EAxis::X), Vector2DValue.Y);
	OwningCharacter->AddMovementInput(RotationMatrix.GetScaledAxis(EAxis::Y), Vector2DValue.X);

	if (bIsSprint && (Vector2DValue.Y <= 0.f || Vector2DValue.X != 0.f))
	{
		SprintEndAction(FInputActionValue());
	}
}

void UMoveComponent::LookAction(const FInputActionValue& Value)
{
	// UE_LOG(LogTemp, Warning, TEXT("UMoveComponent::LookAction"));

	FVector2D Vector2DValue = Value.Get<FVector2D>();

	OwningCharacter->AddControllerPitchInput(-Vector2DValue.Y);
	OwningCharacter->AddControllerYawInput(Vector2DValue.X);
}

void UMoveComponent::CrouchAction(const FInputActionValue& Value)
{
	if (OwningCharacter->bIsCrouched)
	{
		OwningCharacter->UnCrouch();
	}
	else
	{
		OwningCharacter->Crouch();	
	}
}

void UMoveComponent::SprintStartAction(const FInputActionValue& Value)
{
	// Todo : To need to check Stemina from Status Component
	auto CharacterMovement = OwningCharacter->GetCharacterMovement();
	if (CharacterMovement->IsCrouching())
	{
		OwningCharacter->UnCrouch();
	}

	bIsSprint = true;
	ServerRPC_SetMaxWalkSpeed(600.f);
}

void UMoveComponent::SprintEndAction(const FInputActionValue& Value)
{
	if (bIsSprint)
	{
		bIsSprint = false;
		ServerRPC_SetMaxWalkSpeed(300.f);	
	}
}

void UMoveComponent::ServerRPC_SetMaxWalkSpeed_Implementation(float NewMaxWalkSpeed)
{
	MultiRPC_SetMaxWalkSpeed(NewMaxWalkSpeed);
}

void UMoveComponent::MultiRPC_SetMaxWalkSpeed_Implementation(float NewMaxWalkSpeed)
{
	OwningCharacter->GetCharacterMovement()->MaxWalkSpeed = NewMaxWalkSpeed;
}