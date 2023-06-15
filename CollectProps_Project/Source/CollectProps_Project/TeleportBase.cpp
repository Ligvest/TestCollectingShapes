// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportBase.h"
#include "Templates/UnrealTemplate.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
ATeleportBase::ATeleportBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StartPoint = FVector{0.f};
	EndPoint = FVector{0.f};
}

// Called when the game starts or when spawned
void ATeleportBase::BeginPlay()
{
	Super::BeginPlay();
	
	StartPoint = GetActorLocation();
	EndPoint = StartPoint + EndPoint; // Converting relative coordinates of EndPoint to world coordinates
}

void ATeleportBase::SwapStartAndEndPoints(FVector& Start, FVector& End)
{
	Swap(Start, End);
}

// Called every frame
void ATeleportBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleportBase::PerformTeleport()
{
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	if(Character){
		Character->SetActorLocation(EndPoint);
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 300.0f, FColor::Yellow, FString::Printf(TEXT("Teleported")));
	}
}

