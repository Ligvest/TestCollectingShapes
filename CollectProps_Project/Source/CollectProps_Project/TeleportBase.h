// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "TeleportBase.generated.h"

UCLASS()
class COLLECTPROPS_PROJECT_API ATeleportBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportBase();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Platform)
	UStaticMeshComponent* mesh_;

	UPROPERTY(EditAnywhere, Category = Platform)
	FVector StartPoint;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = "true"), Category = Platform)
	FVector EndPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PerformTeleport();
};
