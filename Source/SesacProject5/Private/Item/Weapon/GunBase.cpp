// copyright by LootingEmployment


#include "Item/Weapon/GunBase.h"

#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Projectile/ProjectileBase.h"

// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SetRootComponent(SkeletalMeshComponent);

	FireArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("FireArrowComponent"));
	FireArrowComponent->SetupAttachment(SkeletalMeshComponent);
}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetActorTickEnabled(true);

		CurrentFireCoolDown = FireCoolDown;
	}
	else
	{
		SetActorTickEnabled(false);
	}
}

void AGunBase::OnRep_Owner()
{
	Super::OnRep_Owner();

	OwningCharacter = Cast<ACharacter>(Owner);
}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentFireCoolDown < FireCoolDown) CurrentFireCoolDown += DeltaTime;

	if (bIsTriggered && CurrentFireCoolDown >= FireCoolDown)
	{
		// Todo : Check Ammo
		CurrentFireCoolDown -= FireCoolDown;
		
		// Todo : Fire Bullet;
		
	}
}

void AGunBase::StartFire()
{
	ServerRPC_StartFire();
}

void AGunBase::StopFire()
{
	ServerRPC_StopFire();
}

void AGunBase::FireBullet()
{
	UE_LOG(LogTemp, Warning, TEXT("AGunBase::FireBullet) Debug1"));

	if (OwningCharacter->IsLocallyControlled())
	{
		OwningCharacter->AddControllerPitchInput(FMath::RandRange(-0.f, -1.f));
		OwningCharacter->AddControllerYawInput(FMath::RandRange(-1.0f, 1.0f));
	}
	
	if (BulletClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("AGunBase::FireBullet) Debug2"));
		AProjectileBase* Bullet = GetWorld()->SpawnActor<AProjectileBase>(BulletClass, FireArrowComponent->GetComponentLocation(), FireArrowComponent->GetComponentRotation());
	}
}

void AGunBase::ServerRPC_FireBullet_Implementation()
{
}

void AGunBase::MultiRPC_StartFire_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("MultiRPC_StartFire_Implementation) Debug 1"));
	if (OwningCharacter && FireMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("MultiRPC_StartFire_Implementation) Debug 2"));
		OwningCharacter->PlayAnimMontage(FireMontage);
	}
}

void AGunBase::MultiRPC_StopFire_Implementation()
{
	if (OwningCharacter && FireMontage)
    {
		UE_LOG(LogTemp, Warning, TEXT("MultiRPC_StopFire_Implementation"));
    	OwningCharacter->StopAnimMontage(FireMontage);
    }
}

void AGunBase::ServerRPC_StopFire_Implementation()
{
	bIsTriggered = false;
	MultiRPC_StopFire();
}

void AGunBase::ServerRPC_StartFire_Implementation()
{
	bIsTriggered = true;
	MultiRPC_StartFire();
}