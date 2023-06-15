// Fill out your copyright notice in the Description page of Project Settings.

#include "PropInteractComponent.h"
#include "CollectPropsGameState.h"
#include "Kismet/GameplayStatics.h"

void UPropInteractComponent::BeginPlay()
{
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ACollectProps_ProjectGameMode* GameMode = Cast<ACollectProps_ProjectGameMode>(GameModeBase);
	if (GameMode) {
		if(GameMode->PropTypeToCollect == PropType){
			Super::bIsEnabled = true;
		}
		else {
			Super::bIsEnabled = false;
		}
	}

	Super::BeginPlay();
}

void UPropInteractComponent::Interact()
{
	AGameStateBase* GameStateBase = UGameplayStatics::GetGameState(this);
	ACollectPropsGameState* GameState = Cast<ACollectPropsGameState>(GameStateBase);
	if (GameState) {
		GameState->IncrementPropsCounter();
	}
	OnInteract();
}
