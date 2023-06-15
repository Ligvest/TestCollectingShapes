// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractCollisionBase.h"

//UInteractCollisionBase::UInteractCollisionBase()
//{
//}

void UInteractCollisionBase::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UInteractCollisionBase::OnBoxBeginOverlap);
}

void UInteractCollisionBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	ACollectProps_ProjectCharacter* Character = Cast<ACollectProps_ProjectCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnOverlap.Broadcast(Character, PropType);

		// Unregister from the Overlap Event so it is no longer triggered
		//OnComponentBeginOverlap.RemoveAll(this);
	}
}
