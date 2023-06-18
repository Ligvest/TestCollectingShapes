// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectPropsGameState.h"
#include "CollectPropsHUD.h"
#include "CollectPropsGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ACollectPropsGameState::ACollectPropsGameState() {

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = false;
	PrimaryActorTick.TickGroup = TG_PostUpdateWork;

	SecondsBeforeGameOver = 120;

	// Only the server executes this line as clients can't access GameMode
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	ACollectProps_ProjectGameMode* GameMode = Cast<ACollectProps_ProjectGameMode>(GameModeBase);
	if (GameMode) {
		// Initialize target amount of props
		NumberOfPropsToCollect = GameMode->NumberOfPropsToCollect;

		// Initialize PropType
		PropTypeToCollect = GameMode->PropTypeToCollect;

		// Create a timer with time left before game over
		SecondsBeforeGameOver = GameMode->TimeLeftBeforeGameOver;
	}



	// Initial number of collected props
	PropsCounter = 0;
}

void ACollectPropsGameState::BeginPlay()
{
	GetWorldTimerManager().SetTimer(TimerBeforeGameOver, this, &ACollectPropsGameState::YouLose, SecondsBeforeGameOver, false);
}

void ACollectPropsGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACollectPropsGameState, PropTypeToCollect);
	DOREPLIFETIME(ACollectPropsGameState, NumberOfPropsToCollect);
	DOREPLIFETIME(ACollectPropsGameState, PropsCounter);
	DOREPLIFETIME(ACollectPropsGameState, SecondsBeforeGameOver);
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
		RestartLevel();
	}
}

void ACollectPropsGameState::YouLose()
{
	ACollectPropsHUD* HUD = GetHud();
	if (HUD) {
		HUD->LoseMessage();
		RestartLevel();
	}
}

void ACollectPropsGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TimerBeforeGameOver.IsValid()) {
		ACollectPropsHUD* HUD = GetHud();
		if (HUD) {
			SecondsBeforeGameOver = UKismetSystemLibrary::K2_GetTimerRemainingTimeHandle(this, TimerBeforeGameOver);
			HUD->UpdateTimer(SecondsBeforeGameOver);
		}
	}
}

void ACollectPropsGameState::Rep_PropsCounter()
{
	ACollectPropsHUD* HUD = GetHud();
	if (HUD) {
		HUD->IncrementPropsCounter();
	}

	if (PropsCounter == NumberOfPropsToCollect) {
		YouWon();
	}
}

void ACollectPropsGameState::Rep_OnSecondsBeforeGameOverUpdate()
{
	ACollectPropsHUD* HUD = GetHud();
	if (HUD) {
		HUD->UpdateTimer(SecondsBeforeGameOver);
	}
}

void ACollectPropsGameState::RestartLevel()
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0); PC) {
		if(PC->GetLocalRole() == ROLE_Authority) {
			UCollectPropsGameInstance* GameInstance = GetGameInstance<UCollectPropsGameInstance>();
			if (GameInstance) {
				// Create a timer to wait a little before game restart
				FTimerHandle TimerHandle;
				float SecondsToWait = 3.f;
				GetWorldTimerManager().SetTimer(TimerHandle, GameInstance, &UCollectPropsGameInstance::RestartLevel, SecondsToWait, false);
			}
		}
	}
}


ACollectPropsHUD* ACollectPropsGameState::GetHud()
{	
	ACollectPropsHUD* HUD = nullptr;
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0); PC) {
		HUD = PC->GetHUD<ACollectPropsHUD>();
	}

	return HUD;
}
