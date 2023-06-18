// Copyright Epic Games, Inc. All Rights Reserved.

#include "CollectProps_ProjectGameMode.h"
#include "CollectProps_ProjectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "CollectPropsGameState.h"

ACollectProps_ProjectGameMode::ACollectProps_ProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;


	// Choose which props to collect
	uint8 PropIndex = 0;
	PropIndex = FMath::RandRange(0, 2);
	PropTypeToCollect = static_cast<EPropType>(PropIndex);

	NumberOfPropsToCollect = FMath::RandRange(5, 15);

	// 3 mins by defaut but could be changed in blueprints
	TimeLeftBeforeGameOver = 180.f;
}

void ACollectProps_ProjectGameMode::InitGameState_Implementation()
{
	if (ACollectPropsGameState* MyGameState = GetGameState<ACollectPropsGameState>(); MyGameState) {
		MyGameState->NumberOfPropsToCollect = NumberOfPropsToCollect;
		MyGameState->PropTypeToCollect = PropTypeToCollect;
	}
}

void ACollectProps_ProjectGameMode::BeginPlay()
{
	ACharacter* CharacterBase = UGameplayStatics::GetPlayerCharacter(this, 0);
	ACollectProps_ProjectCharacter* Character = Cast<ACollectProps_ProjectCharacter>(CharacterBase);
	//Character->InitializeHUD(this);
}
