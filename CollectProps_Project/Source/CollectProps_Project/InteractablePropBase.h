// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectProps_ProjectGameMode.h"

#include "InteractablePropBase.generated.h"

UCLASS()
class COLLECTPROPS_PROJECT_API AInteractablePropBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractablePropBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	EPropType PropType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	class USceneComponent* SceneComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	class UPropInteractComponent* InteractCollision;

    // Static Mesh used to provide a visual representation of the object.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
    class UStaticMeshComponent* StaticMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
