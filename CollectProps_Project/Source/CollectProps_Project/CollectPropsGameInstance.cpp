// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectPropsGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UCollectPropsGameInstance::RestartLevel()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(*CurrentLevelName));
}
