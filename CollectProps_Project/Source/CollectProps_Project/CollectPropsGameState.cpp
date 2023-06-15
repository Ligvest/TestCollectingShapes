// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectPropsGameState.h"
#include "CollectPropsHUD.h"
#include "CollectPropsGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

ACollectPropsGameState::ACollectPropsGameState() {

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = false;
	PrimaryActorTick.TickGroup = TG_PostUpdateWork;

	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ACollectProps_ProjectGameMode* GameMode = Cast<ACollectProps_ProjectGameMode>(GameModeBase);
	if (GameMode) {
		NumberOfPropsToCollect = GameMode->NumberOfPropsToCollect;

		// Create a timer with time left before game over
		float SecondsBeforeGameOver = GameMode->TimeLeftBeforeGameOver;
		GetWorldTimerManager().SetTimer(TimerBeforeGameOver, this, &ACollectPropsGameState::YouLose, SecondsBeforeGameOver, false);
	}


	PropsCounter = 0;
}

void ACollectPropsGameState::IncrementPropsCounter()
{
	ACollectPropsHUD* HUD = GetHud();
	if (HUD) {
		++PropsCounter;
		HUD->IncrementPropsCounter();

		if (PropsCounter == NumberOfPropsToCollect) {
			YouWon();
		}
	}
}

void ACollectPropsGameState::YouWon()
{
	ACollectPropsHUD* HUD = GetHud();
	if (HUD) {
		HUD->WinMessage();
		UCollectPropsGameInstance* GameInstance = GetGameInstance<UCollectPropsGameInstance>();
		if (GameInstance) {

			// Create a timer to wait a little before game restart
			FTimerHandle TimerHandle;
			float SecondsToWait = 3.f;
			GetWorldTimerManager().SetTimer(TimerHandle, GameInstance, &UCollectPropsGameInstance::RestartLevel, SecondsToWait, false);
		}
	}
}

void ACollectPropsGameState::YouLose()
{
	ACollectPropsHUD* HUD = GetHud();
	if (HUD) {
		HUD->LoseMessage();
		UCollectPropsGameInstance* GameInstance = GetGameInstance<UCollectPropsGameInstance>();
		if (GameInstance) {

			// Create a timer to wait a little before game restart
			FTimerHandle TimerHandle;
			float SecondsToWait = 3.f;
			GetWorldTimerManager().SetTimer(TimerHandle, GameInstance, &UCollectPropsGameInstance::RestartLevel, SecondsToWait, false);
		}
	}
}

void ACollectPropsGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TimerBeforeGameOver.IsValid()) {
		ACollectPropsHUD* HUD = GetHud();
		if (HUD) {
			float SecondsBeforeGameOver = UKismetSystemLibrary::K2_GetTimerRemainingTimeHandle(this, TimerBeforeGameOver);
			HUD->UpdateTimer(SecondsBeforeGameOver);
		}
	}
}

ACollectPropsHUD* ACollectPropsGameState::GetHud()
{	
	ACollectPropsHUD* HUD = nullptr;

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC) {
		HUD = PC->GetHUD<ACollectPropsHUD>();
	}

	return HUD;
}
