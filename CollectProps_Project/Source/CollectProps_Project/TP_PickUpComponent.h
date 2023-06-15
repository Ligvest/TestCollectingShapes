// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "CollectProps_ProjectCharacter.h"
#include "TP_PickUpComponent.generated.h"

// Is called when overlap happens
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOverlap, ACollectProps_ProjectCharacter*, OverlappedCharacter, EPropType, PropType);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class COLLECTPROPS_PROJECT_API UTP_PickUpComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	/** Prop type to differentiate different shapes */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPropType PropType;

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnOverlap OnOverlap;

	UTP_PickUpComponent();
protected:

	/** Called when the game starts */
	virtual void BeginPlay() override;

	/** Code for when something overlaps this component */
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};