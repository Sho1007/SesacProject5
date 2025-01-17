// copyright by LootingEmployment

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPSAnimInstance.generated.h"

class UHealthComponent;
class ACharacterBase;
class UWeaponComponent;
/**
 * 
 */
UCLASS()
class SESACPROJECT5_API UFPSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
public:
	UFUNCTION()
	void Die(bool bNewIsDead);

	UFUNCTION()
	void AnimNotify_OnDieEnd();

	UFUNCTION()
	void AnimNotify_OnReloadEnd();

	UFUNCTION()
	void UpdateIsSprint(bool bNewIsSprint);
	UFUNCTION()
	void UpdateIsAiming(bool bNewIsAiming);
	UFUNCTION()
	void UpdateHandSwayFloats(float NewSidMove, float NewMouseX, float NewMouseY);
	UFUNCTION()
	void UpdateLeftHandIK(FTransform NewLeftHandIK);

	UFUNCTION(BlueprintNativeEvent)
	void ProcedualRecoil(float Multiplier);

	void LeanInterpolaction(float DeltaSeconds);

	UFUNCTION()
	void UpdateLeanBoolean(bool bNewLeanLeft, bool bNewLeanRight);

	void SetWallTargetValue(float NewWallTargetValue);

	UFUNCTION(BlueprintCallable)
	void SetLeftHandIKAlpha(float NewLeftHandIKAlpha);
	
private:
	UPROPERTY()
	ACharacterBase* OwningCharacter;
	UPROPERTY()
	UHealthComponent* HealthComponent;
	UPROPERTY()
	UWeaponComponent* WeaponComponent;
	
	// Check Wall
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float WallValue = 1.f;
	
	UPROPERTY()
	bool bIsDead = false;
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess))
	bool bIsCrouch = false;
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess))
	bool bIsSprint = false;
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess))
	bool bIsAiming = false;
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float SideMove;
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float MouseX;
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float MouseY;


	// Lean Function
	UPROPERTY()
	bool bLeanLeft = false;
	UPROPERTY()
	bool bLeanRight = false;
	UPROPERTY()
	float LeanAmount = 0.f;
	UPROPERTY()
	float LeanTarget = 0.f;
	UPROPERTY()
	float LeanSpeed = 10.f;
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float LeanMultiplier = 15.f;
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess))
	FRotator LeanRotator;
	
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess))
	FTransform LeftHandSocketTransform;

	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float LeftHandIKAlpha = 1.f;
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float LeftHandIKAlphaTarget = 1.f;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TArray<UAnimMontage*> DieMontageArray;
};