// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"

class UFPSAnim_CharacterComponent;
struct FInputActionValue;
class UInputAction;
class UEnhancedInputComponent;
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SESACPROJECT5_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetupPlayerInputComponent(UEnhancedInputComponent* PlayerInputComponent);

	void StopSprint();

	void MoveAction(const FInputActionValue& Value);
	void MoveEndAction(const FInputActionValue& Value);
	
	void LookAction(const FInputActionValue& Value);
	void LookEndAction(const FInputActionValue& Value);
	void CrouchAction(const FInputActionValue& Value);
	void SprintStartAction(const FInputActionValue& Value);
	void SprintEndAction(const FInputActionValue& Value);
	void JumpAction(const FInputActionValue& Value);
	void LeanLeftStartAction(const FInputActionValue& Value);
	void LeanLeftEndAction(const FInputActionValue& Value);
	void LeanRightStartAction(const FInputActionValue& Value);
	void LeanRightEndAction(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void ServerRPC_StartSprint();
	UFUNCTION(Server, Reliable)
	void ServerRPC_StopSprint();

	UFUNCTION(Server, Reliable)
	void ServerRPC_SetLeanLeft(bool bNewLeanLeft);
	UFUNCTION(Server, Reliable)
	void ServerRPC_SetLeanRight(bool bNewLeanRight);
	
	UFUNCTION()
	void OnRep_IsSprint();

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	UFUNCTION()
	void SwayFloatTimerFunction();

	UFUNCTION()
	void OnRep_Lean();
	
private:
	// Lean
	UPROPERTY(ReplicatedUsing = OnRep_Lean, Meta = (AllowPrivateAccess))
	bool bLeanLeft = false;
	UPROPERTY(ReplicatedUsing = OnRep_Lean, Meta = (AllowPrivateAccess))
	bool bLeanRight = false;
	
	UPROPERTY()
	FTimerHandle SwayFloatTimerHandle;

	float SideMove;
	float MouseX;
	float MouseY;
	
	UPROPERTY(ReplicatedUsing = OnRep_IsSprint, Meta = (AllowPrivateAccess))
	bool bIsSprint = false;
	
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	UInputAction* IA_Move;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	UInputAction* IA_Look;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	UInputAction* IA_Crouch;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	UInputAction* IA_Sprint;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	UInputAction* IA_Jump;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	UInputAction* IA_LeanLeft;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	UInputAction* IA_LeanRight;

	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	ACharacter* OwningCharacter;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FDele_IsSprint, bool);
	FDele_IsSprint OnIsSprintChanged;

	// Side Move, MouseX, MouseY
	DECLARE_DELEGATE_ThreeParams(FDele_HandSway, float, float, float);
	FDele_HandSway OnHandSwayFloatsChanged;

	// LeanLeft, LeanRight
	DECLARE_DELEGATE_TwoParams(FDele_Lean, bool, bool);
	FDele_Lean OnLeanChanged;
};