// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractCollisionBase.h"
#include "TeleportInteractCollision.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class COLLECTPROPS_PROJECT_API UTeleportInteractCollision : public UInteractCollisionBase
{
	GENERATED_BODY()
	
public:

	virtual void Interact(AActor* Interactor) override;
};
