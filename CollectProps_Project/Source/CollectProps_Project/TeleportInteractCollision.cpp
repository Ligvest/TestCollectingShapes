// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportInteractCollision.h"
#include "TeleportBase.h"

void UTeleportInteractCollision::Interact()
{
	ATeleportBase* TeleportActor = GetOwner<ATeleportBase>();
	if (TeleportActor) {
		TeleportActor->PerformTeleport();
	}
}
