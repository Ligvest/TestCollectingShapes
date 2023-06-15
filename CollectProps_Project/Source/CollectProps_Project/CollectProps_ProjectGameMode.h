// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CollectProps_ProjectGameMode.generated.h"

UENUM(BlueprintType)
enum class EPropType : uint8 {
	EPT_Cube UMETA(DisplayName = "Cube"),
	EPT_Sphere UMETA(DisplayName = "Sphere"),
	EPT_Cylinder UMETA(DisplayName = "Cylinder"),

	EPropType_End UMETA(DisplayName = "EndOfEnumeration"),
};


UCLASS(minimalapi)
class ACollectProps_ProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	EPropType PropTypeToCollect;

	UPROPERTY(BlueprintReadOnly)
	int32 NumberOfPropsToCollect;

public:
	ACollectProps_ProjectGameMode();
};



