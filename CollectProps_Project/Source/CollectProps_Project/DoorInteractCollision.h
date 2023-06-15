// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractCollisionBase.h"
#include "DoorInteractCollision.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class COLLECTPROPS_PROJECT_API UDoorInteractCollision : public UInteractCollisionBase
{
	GENERATED_BODY()

public:
	virtual void Interact() override;
};
