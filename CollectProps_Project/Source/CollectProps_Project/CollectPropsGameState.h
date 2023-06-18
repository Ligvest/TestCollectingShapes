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

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;

public:
	// Called on each prop pickup
	void IncrementPropsCounter();

	// Called in case of success
	void YouWon();

	// Called in case of fail
	void YouLose();

	// Timer before the player loses
	FTimerHandle TimerBeforeGameOver;

	UPROPERTY(ReplicatedUsing = Rep_OnSecondsBeforeGameOverUpdate, BlueprintReadOnly)
	float SecondsBeforeGameOver;


	virtual void Tick( float DeltaSeconds ) override;

public:

	UPROPERTY(Replicated, BlueprintReadOnly)
	EPropType PropTypeToCollect;

	UPROPERTY(ReplicatedUsing = Rep_PropsCounter, BlueprintReadOnly)
	int32 PropsCounter;

	UFUNCTION()
	void Rep_PropsCounter();

	UFUNCTION()
	void Rep_OnSecondsBeforeGameOverUpdate();

	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 NumberOfPropsToCollect;

	//UFUNCTION(Server, Reliable)
	void RestartLevel();

protected:
	class ACollectPropsHUD* GetHud();

};
