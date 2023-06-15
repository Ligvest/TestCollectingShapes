// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CollectPropsHUD.generated.h"

/**
 * 
 */
UCLASS()
class COLLECTPROPS_PROJECT_API ACollectPropsHUD : public AHUD
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintImplementableEvent)
	void IncrementPropsCounter();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTimer(int32 NewTimerValue);

	UFUNCTION(BlueprintImplementableEvent)
	void WinMessage();

	UFUNCTION(BlueprintImplementableEvent)
	void LoseMessage();
};
