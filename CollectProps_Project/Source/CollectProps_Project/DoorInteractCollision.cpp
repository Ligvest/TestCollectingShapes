// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractCollision.h"
#include "Kismet/GameplayStatics.h"
#include "CollectProps_ProjectCharacter.h"
#include "InteractableDoorBase.h"

void UDoorInteractCollision::Interact(AActor* Interactor)
{
	if(AInteractableDoorBase* DoorActor = GetOwner<AInteractableDoorBase>(); DoorActor) {
		if (ACharacter* CharacterBase = UGameplayStatics::GetPlayerCharacter(this, 0); CharacterBase) {
			if (ACollectProps_ProjectCharacter* Character = Cast<ACollectProps_ProjectCharacter>(CharacterBase); Character) {
				Character->AskServerToOpenDoor(DoorActor);
			}
		}

		DoorActor->Open();
	}
}
