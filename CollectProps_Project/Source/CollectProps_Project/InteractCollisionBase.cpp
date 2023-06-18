// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractCollisionBase.h"

UInteractCollisionBase::UInteractCollisionBase()
{
	bIsEnabled = true;
}

void UInteractCollisionBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInteractCollisionBase, bIsEnabled);
}

void UInteractCollisionBase::SetIsEnabled(bool bNewIsEnabled)
{
	bIsEnabled = bNewIsEnabled;
}

void UInteractCollisionBase::BeginPlay()
{
	Super::BeginPlay();		

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UInteractCollisionBase::OnBoxBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UInteractCollisionBase::OnBoxEndOverlap);
}

void UInteractCollisionBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsEnabled) {
		OnComponentBeginOverlap.RemoveDynamic(this, &UInteractCollisionBase::OnBoxBeginOverlap);
		OnComponentEndOverlap.RemoveDynamic(this, &UInteractCollisionBase::OnBoxEndOverlap);
		return;
	}

	// Checking if it is a First Person Character overlapping
	ACollectProps_ProjectCharacter* Character = Cast<ACollectProps_ProjectCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		Character->CurrentInteractionObject = this;
	}
}

void UInteractCollisionBase::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!bIsEnabled) {
		OnComponentBeginOverlap.RemoveDynamic(this, &UInteractCollisionBase::OnBoxBeginOverlap);
		OnComponentEndOverlap.RemoveDynamic(this, &UInteractCollisionBase::OnBoxEndOverlap);
		return;
	}

	// Checking if it is a First Person Character overlapping
	ACollectProps_ProjectCharacter* Character = Cast<ACollectProps_ProjectCharacter>(OtherActor);
	if(Character != nullptr)
	{
		Character->CurrentInteractionObject = nullptr;
	}
}
