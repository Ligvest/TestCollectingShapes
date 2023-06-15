// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectPropsGameState.h"
#include "CollectPropsHUD.h"
#include "Kismet/GameplayStatics.h"

ACollectPropsGameState::ACollectPropsGameState() {

	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ACollectProps_ProjectGameMode* GameMode = Cast<ACollectProps_ProjectGameMode>(GameModeBase);
	if (GameMode) {
		NumberOfPropsToCollect = GameMode->NumberOfPropsToCollect;
	}

	PropsCounter = 0;
}

void ACollectPropsGameState::IncrementPropsCounter()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC) {
		ACollectPropsHUD* HUD = PC->GetHUD<ACollectPropsHUD>();
		if (HUD) {
			++PropsCounter;
			HUD->IncrementPropsCounter();

			if (PropsCounter == NumberOfPropsToCollect) {
				HUD->WinMessage();
			}
		}
	}
}
