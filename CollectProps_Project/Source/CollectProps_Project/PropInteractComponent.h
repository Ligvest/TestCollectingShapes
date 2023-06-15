// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractCollisionBase.h"
#include "CollectProps_ProjectGameMode.h"
#include "PropInteractComponent.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPropPickup);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class COLLECTPROPS_PROJECT_API UPropInteractComponent : public UInteractCollisionBase
{
	GENERATED_BODY()

protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract();

	virtual void Interact() override;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPropPickup OnPropPickup;

public:
	UPROPERTY(EditDefaultsOnly);
	EPropType PropType;
};
