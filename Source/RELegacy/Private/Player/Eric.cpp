// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Eric.h"
#include "Player/InputDataConfig.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Items/Item.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AEric::AEric()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Setting rotation to false
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Adding CameraBoom component to Root component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;

	// Adding Camera component and attachig to CameraBoom
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraBoom);

	// Adding Sphere collision component
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

	GetMesh()->SetGenerateOverlapEvents(true);
}

// Called every frame
void AEric::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEric::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(GContext, 0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (InputActions) {

			Input->BindAction(InputActions->MovementAction, ETriggerEvent::Triggered, this, &AEric::Move);
			Input->BindAction(InputActions->LookAction, ETriggerEvent::Triggered, this, &AEric::Look);
			Input->BindAction(InputActions->InteractAction, ETriggerEvent::Triggered, this, &AEric::Interact);

		}
	}

}



// Called when the game starts or when spawned
void AEric::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("Player"));
	
}

void AEric::Move(const FInputActionValue& Value)
{
	// Setting Movement vector to 2D vector based on input value
	const FVector2D MovementVector = Value.Get<FVector2D>();

	// Checking if controller is not nullptr and movevent vector is not zero vector
	if (Controller && (MovementVector != FVector2D::ZeroVector))
	{
		//Movement direction depends on rotation
		const FRotator ControlRotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Adding movement depending on X and Y of movenent vector
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

	}

}

void AEric::Look(const FInputActionValue& Value)
{
	// Gets look vector from Value input
	FVector2D LookVector = Value.Get<FVector2D>();

	// Checking if controller is not nullptr and LookVector is not zero vector
	if (Controller && (LookVector != FVector2D::ZeroVector))
	{
		//Adding corresponding X and Y values to input 
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}

}

void AEric::Interact()
{
	// Checking if object is AItem
	AItem* InteractableItem = Cast<AItem>(OverlappingItem);

	// Checking if not nullptr
	if (InteractableItem)
	{
		// Calling Interact() function of the object we are interracting with
		InteractableItem->Interact();
	}
}

void AEric::SetOverlappingItem(AItem* Item)
{
	// Set OverlappingItem to Item we overlap with 
	OverlappingItem = Item;
}





