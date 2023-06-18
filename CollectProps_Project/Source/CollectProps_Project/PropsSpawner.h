// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"

#include "PropsSpawner.generated.h"

UCLASS()
class COLLECTPROPS_PROJECT_API APropsSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APropsSpawner();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawning)
	class UBoxComponent* spawningBox_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
	TSubclassOf<AActor> actorToSpawn1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
	TSubclassOf<AActor> actorToSpawn2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
	TSubclassOf<AActor> actorToSpawn3;

protected:
	TSubclassOf<AActor> GetRandActorToSpawn() const;

	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintPure, Category = Spawning)
	FVector GetSpawnPoint() const;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Spawning")
	void SpawnRandomActor();

};
