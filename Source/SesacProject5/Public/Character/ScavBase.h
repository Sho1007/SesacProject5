// copyright by LootingEmployment

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "ScavBase.generated.h"

class UFSMComponent;
/**
 * 
 */
UCLASS()
class SESACPROJECT5_API AScavBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	AScavBase();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="MySettings|Component")
	UFSMComponent* FSMComp;
};