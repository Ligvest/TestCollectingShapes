// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectProps_ProjectGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "CollectPropsGameState.generated.h"

/**
 * 
 */
UCLASS()
class COLLECTPROPS_PROJECT_API ACollectPropsGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ACollectPropsGameState();

public:
	// Called on each prop pickup
	void IncrementPropsCounter();

	// Called in case of success
	void YouWon();

	// Called in case of fail
	void YouLose();

	// Timer before the player loses
	FTimerHandle TimerBeforeGameOver;


	virtual void Tick( float DeltaSeconds ) override;

public:
	EPropType PropTypeToCollect;
	int32 PropsCounter;
	int32 NumberOfPropsToCollect;

protected:
	class ACollectPropsHUD* GetHud();

};
