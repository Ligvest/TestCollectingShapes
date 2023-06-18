// Fill out your copyright notice in the Description page of Project Settings.

#include "PropInteractComponent.h"
#include "CollectPropsGameState.h"
#include "InteractablePropBase.h"
#include "CollectProps_ProjectCharacter.h"
#include "Kismet/GameplayStatics.h"

void UPropInteractComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPropInteractComponent, PropType);
}

void UPropInteractComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPropInteractComponent::Interact(AActor* Interactor)
{
	AGameStateBase* GameStateBase = UGameplayStatics::GetGameState(this);
	ACollectPropsGameState* GameState = Cast<ACollectPropsGameState>(GameStateBase);
	if (GameState) {
		GameState->IncrementPropsCounter();
		//OnPropPickup.Broadcast();
	}
	
	// Destroy actor on the Server
	if (AInteractablePropBase* PropActor = GetOwner<AInteractablePropBase>(); PropActor) {
		if (ACharacter* CharacterBase = UGameplayStatics::GetPlayerCharacter(this, 0); CharacterBase) {
			if (ACollectProps_ProjectCharacter* Character = Cast<ACollectProps_ProjectCharacter>(CharacterBase); Character) {
				Character->AskServerToDestroyActor(PropActor);
			}
		}
	}
	//OnInteract();
}

void UPropInteractComponent::SetPropType(EPropType NewPropType)
{
	PropType = NewPropType;
}
