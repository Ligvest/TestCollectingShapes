// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractCollisionBase.h"

UInteractCollisionBase::UInteractCollisionBase()
{
	bIsEnabled = true;
}

void UInteractCollisionBase::BeginPlay()
{
	Super::BeginPlay();		

	if(bIsEnabled){
		// Register our Overlap Event
		OnComponentBeginOverlap.AddDynamic(this, &UInteractCollisionBase::OnBoxBeginOverlap);
		OnComponentEndOverlap.AddDynamic(this, &UInteractCollisionBase::OnBoxEndOverlap);
	}
}

void UInteractCollisionBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	ACollectProps_ProjectCharacter* Character = Cast<ACollectProps_ProjectCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		Character->CurrentInteractionObject = this;
		//OnOverlap.Broadcast(Character, PropType);
	}
}

void UInteractCollisionBase::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Checking if it is a First Person Character overlapping
	ACollectProps_ProjectCharacter* Character = Cast<ACollectProps_ProjectCharacter>(OtherActor);
	if(Character != nullptr)
	{
		Character->CurrentInteractionObject = nullptr;
	}
}
