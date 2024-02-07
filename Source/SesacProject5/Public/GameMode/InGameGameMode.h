// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InGameGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SESACPROJECT5_API AInGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AInGameGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
};