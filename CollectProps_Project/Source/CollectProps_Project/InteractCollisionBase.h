// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "CollectProps_ProjectCharacter.h"
#include "InteractCollisionBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractableActorOverlap, ACollectProps_ProjectCharacter*, OverlappedCharacter, EPropType, PropType);

UCLASS()
class COLLECTPROPS_PROJECT_API UInteractCollisionBase : public UBoxComponent
{
	GENERATED_BODY()

public:
	/** Prop type to differentiate different shapes */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPropType PropType;

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractableActorOverlap OnOverlap;

protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;

	/** Code for when something overlaps this component */
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
