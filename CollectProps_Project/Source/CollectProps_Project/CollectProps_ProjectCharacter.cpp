// Copyright Epic Games, Inc. All Rights Reserved.

#include "CollectProps_ProjectCharacter.h"
#include "CollectProps_ProjectProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "InteractInterface.h"
#include "Net/UnrealNetwork.h"
#include "DoorInteractCollision.h"
#include "Kismet/GameplayStatics.h"
#include "CollectPropsHUD.h"
#include "CollectProps_ProjectGameMode.h"
#include "InteractableDoorBase.h"


//////////////////////////////////////////////////////////////////////////
// ACollectProps_ProjectCharacter

ACollectProps_ProjectCharacter::ACollectProps_ProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

}

void ACollectProps_ProjectCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACollectProps_ProjectCharacter, RepInteractionObject);
}

void ACollectProps_ProjectCharacter::InitializeGameState_Implementation()
{
	if (AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(this); GameModeBase) {
		if (ACollectProps_ProjectGameMode* GameMode = Cast<ACollectProps_ProjectGameMode>(GameModeBase); GameMode) {
			GameMode->InitGameState();
		}
	}
}

void ACollectProps_ProjectCharacter::InitializeHUD_Implementation()
{
	InitializeHUD_MULTI();
}

void ACollectProps_ProjectCharacter::InitializeHUD_MULTI_Implementation()
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0); PC) {
		if (ACollectPropsHUD* HUD = PC->GetHUD<ACollectPropsHUD>(); HUD) {
			HUD->InitializeHUDWidget();
		}
	}
}

void ACollectProps_ProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Initialize GameState for every client
	//InitializeGameState();

	// Initialize HUD for every client
	InitializeHUD();
}

//////////////////////////////////////////////////////////////////////////// Input

void ACollectProps_ProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &ACollectProps_ProjectCharacter::OnPrimaryAction);

	// Bind Interact event
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACollectProps_ProjectCharacter::RequestInteract);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ACollectProps_ProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ACollectProps_ProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Mouse" versions handle devices that provide an absolute delta, such as a mouse.
	// "Gamepad" versions are for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ACollectProps_ProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ACollectProps_ProjectCharacter::LookUpAtRate);
}


void ACollectProps_ProjectCharacter::RequestInteract()
{
	AskServerToPerformInteract(this);
	//OnInteract();
}

void ACollectProps_ProjectCharacter::AskServerToPerformInteract(AActor* Interactor)
{
	Server_OnInteract(Interactor);
}

void ACollectProps_ProjectCharacter::Server_OnInteract_Implementation(AActor* Interactor)
{
	//RepInteractionObject = InteractionObject;
	OnInteract(Interactor);
}

void ACollectProps_ProjectCharacter::Rep_RepInteractionObject()
{
	//OnInteract();
}

void ACollectProps_ProjectCharacter::AskServerToDestroyActor(AActor* ActorToDestroy)
{
	Server_DestroyActor(ActorToDestroy);
}

void ACollectProps_ProjectCharacter::Server_DestroyActor_Implementation(AActor* ActorToDestroy)
{
	ActorToDestroy->Destroy();
}

void ACollectProps_ProjectCharacter::AskServerToOpenDoor(AInteractableDoorBase* DoorToOpen)
{
	Server_OpenDoor(DoorToOpen);
}

void ACollectProps_ProjectCharacter::Server_OpenDoor_Implementation(AInteractableDoorBase* DoorToOpen)
{
	DoorToOpen->Open();
}

void ACollectProps_ProjectCharacter::OnInteract(AActor* Interactor)
{
	//IInteractInterface* PrevInteractionObject = CurrentInteractionObject;
	//CurrentInteractionObject = RepInteractionObject.GetInterface();

	if (CurrentInteractionObject) {
		CurrentInteractionObject->Interact(Interactor);
	}
	else {
		if (GEngine)
		{ 
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Nothing to interact with"));
		}
	}

	// Restore prev value of interaction object
	//CurrentInteractionObject = PrevInteractionObject;
}



void ACollectProps_ProjectCharacter::OnPrimaryAction()
{
	// Trigger the OnItemUsed Event
	OnUseItem.Broadcast();
}

void ACollectProps_ProjectCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnPrimaryAction();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void ACollectProps_ProjectCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

void ACollectProps_ProjectCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ACollectProps_ProjectCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ACollectProps_ProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ACollectProps_ProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

bool ACollectProps_ProjectCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ACollectProps_ProjectCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ACollectProps_ProjectCharacter::EndTouch);

		return true;
	}
	
	return false;
}
