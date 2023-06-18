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

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class COLLECTPROPS_PROJECT_API UPropInteractComponent : public UInteractCollisionBase
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;

public:
	virtual void Interact(AActor* Interactor) override;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnPropPickup OnPropPickup;

public:
	UPROPERTY(Replicated);
	EPropType PropType;

	UFUNCTION(BlueprintCallable)
	void SetPropType(EPropType NewPropType);
};
