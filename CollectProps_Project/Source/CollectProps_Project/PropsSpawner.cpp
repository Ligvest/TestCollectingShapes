// Fill out your copyright notice in the Description page of Project Settings.


#include "PropsSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APropsSpawner::APropsSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	spawningBox_ = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));

}

TSubclassOf<AActor> APropsSpawner::GetRandActorToSpawn() const
{
	TSubclassOf<AActor> actorToSpawn;
	if (actorToSpawn1 && actorToSpawn2 && actorToSpawn3) {
		TArray<TSubclassOf<AActor>> poolOfActors{ actorToSpawn1, actorToSpawn2,actorToSpawn3 };

		if (poolOfActors.Num() > 0) {
			int32 actorNumber = FMath::RandRange(0, poolOfActors.Num() - 1);
			actorToSpawn = poolOfActors[actorNumber];
		}
	}
	return actorToSpawn;
}

void APropsSpawner::BeginPlay()
{
	SpawnRandomActor();
}

FVector APropsSpawner::GetSpawnPoint() const
{
	FVector origin = spawningBox_->GetComponentLocation();
	FVector extent = spawningBox_->GetScaledBoxExtent();

	FVector randPoint = UKismetMathLibrary::RandomPointInBoundingBox(origin, extent);

	return randPoint;
}

void APropsSpawner::SpawnRandomActor_Implementation()
{
	FVector SpawnLocation = GetSpawnPoint();
	TSubclassOf<AActor> actorToSpawn = GetRandActorToSpawn();

	if (actorToSpawn) {
		UWorld* world = GetWorld();

		if (world) {
			FActorSpawnParameters spawnParameters;
			AActor* spawnedActor = world->SpawnActor<AActor>(actorToSpawn, SpawnLocation, FRotator(0.f), spawnParameters);
		}
	}
}

