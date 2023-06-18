// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractablePropBase.h"
#include "PropInteractComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CollectProps_ProjectGameMode.h"

// Sets default values
AInteractablePropBase::AInteractablePropBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	RootComponent = SceneComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetupAttachment(RootComponent);

	InteractCollision = CreateDefaultSubobject<UPropInteractComponent>(TEXT("Interact Collision"));
	InteractCollision->SetupAttachment(StaticMesh);
}

// Called when the game starts or when spawned
void AInteractablePropBase::BeginPlay()
{
	Super::BeginPlay();

	bool bHasAuthority = false;
	if (ACharacter* CharacterBase = UGameplayStatics::GetPlayerCharacter(this, 0); CharacterBase) {
		if (ACollectProps_ProjectCharacter* Character = Cast<ACollectProps_ProjectCharacter>(CharacterBase); Character) {
			bHasAuthority = Character->HasAuthority();
		}
	}

	if (!bHasAuthority) {
		return;
	}

	InteractCollision->SetPropType(PropType);
	if(AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(this); GameModeBase){
		if (ACollectProps_ProjectGameMode* GameMode = Cast<ACollectProps_ProjectGameMode>(GameModeBase); GameMode) {
			if (!(GameMode->PropTypeToCollect == PropType) ){
				InteractCollision->DestroyComponent();
			}
		}
	}
}

// Called every frame
void AInteractablePropBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

