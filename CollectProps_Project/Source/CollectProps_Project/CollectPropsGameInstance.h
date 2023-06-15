// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CollectPropsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class COLLECTPROPS_PROJECT_API UCollectPropsGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void RestartLevel();
};
