// Copyright Epic Games, Inc. All Rights Reserved.

#include "CollectProps_ProjectGameMode.h"
#include "CollectProps_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACollectProps_ProjectGameMode::ACollectProps_ProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// Choose which props to collect
	uint8 PropIndex = 0;
	PropIndex = FMath::RandRange(0, 2);
	PropsToCollect = static_cast<EPropType>(PropIndex);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 300.0f, FColor::Yellow, FString::Printf(TEXT("Prop index is \"%d\""), PropIndex));
	}
}
