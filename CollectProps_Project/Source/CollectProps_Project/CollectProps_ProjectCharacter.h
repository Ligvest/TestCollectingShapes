// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Templates/SharedPointer.h"
#include "Net/UnrealNetwork.h"

#include "CollectProps_ProjectCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

// Declaration of the delegate that will be called when the Primary Action is triggered
// It is declared as dynamic so it can be accessed also in Blueprints
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);

UCLASS(config=Game)
class ACollectProps_ProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	ACollectProps_ProjectCharacter();


	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	//UFUNCTION(NetMulticast, Reliable)
	//void InitializeHUD(ACollectProps_ProjectGameMode* GameMode);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void InitializeGameState();

	UFUNCTION(Server, Reliable)
	void InitializeHUD();

	UFUNCTION(NetMulticast, Reliable)
	void InitializeHUD_MULTI();

protected:
	virtual void BeginPlay();

public:
	/** Current object with which we will interact if press interact button (e.g. 'E'). */
	class IInteractInterface* CurrentInteractionObject;

	/** A variable helper for interact replication implementation */
	UPROPERTY(ReplicatedUsing = Rep_RepInteractionObject)
	TScriptInterface<IInteractInterface> RepInteractionObject;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float TurnRateGamepad;

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnUseItem OnUseItem;

	void AskServerToPerformInteract(AActor* Interactor);

	UFUNCTION(Server, Reliable)
	void Server_OnInteract(AActor* Interactor);

	UFUNCTION()
	void Rep_RepInteractionObject();

	UFUNCTION()
	void AskServerToDestroyActor(AActor* ActorToDestroy);

	UFUNCTION(Server, Reliable)
	void Server_DestroyActor(AActor* ActorToDestroy);

	UFUNCTION()
	void AskServerToOpenDoor(AInteractableDoorBase* DoorToOpen);

	UFUNCTION(Server, Reliable)
	void Server_OpenDoor(AInteractableDoorBase* DoorToOpen);

	//UFUNCTION(NetMulticast, Reliable)
	//void Multicast_OpenDoor(AActor* DoorToOpen);

protected:

	/** Interact with an interactable object */
	void OnInteract(AActor* Interactor);

	/** Interact with an interactable object */
	void RequestInteract();
	
	/** Fires a projectile. */
	void OnPrimaryAction();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

