// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractCollision.h"
#include "InteractableDoorBase.h"

void UDoorInteractCollision::Interact()
{
	AInteractableDoorBase* DoorActor = GetOwner<AInteractableDoorBase>();
	if (DoorActor) {
		DoorActor->Open();
	}
}
