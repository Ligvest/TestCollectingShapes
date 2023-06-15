// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "CollectProps_ProjectCharacter.h"
#include "InteractInterface.h"
#include "CollectProps_ProjectGameMode.h"
#include "InteractCollisionBase.generated.h"

/**
 * 
 */

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractableActorOverlap, ACollectProps_ProjectCharacter*, OverlappedCharacter, EPropType, PropType);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class COLLECTPROPS_PROJECT_API UInteractCollisionBase : public UBoxComponent, public IInteractInterface
{
	GENERATED_BODY()

public:
	UInteractCollisionBase();

public:

	/** Delegate to whom anyone can subscribe to receive this event */
	//UPROPERTY(BlueprintAssignable, Category = "Interaction")
	//FOnInteractableActorOverlap OnOverlap;

public:

protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;

	/** Code for when something overlaps this component */
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** Code for when something goes away after overlapping */
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	/** Don't enable if the object shouldn't be used */
	UPROPERTY(BlueprintReadWrite)
	bool bIsEnabled;
};
