// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStaticCamera.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerController.h"

AGameStaticCamera::AGameStaticCamera() 
{

	PrimaryActorTick.bCanEverTick = true;

	//Adding box trigger to a Camera object
	StartTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Start Trigger"));
	StartTrigger->SetupAttachment(GetRootComponent());

	StartTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StartTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

}

void AGameStaticCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if target should be on player and camera is active
	if (bTargetOnPlayer && GetIsCameraActive())
	{
		//Locks target on player
		TargetLockOnPlayer();
	}
}

void AGameStaticCamera::BeginPlay()
{
	Super::BeginPlay();

	StartTrigger->OnComponentBeginOverlap.AddDynamic(this, &AGameStaticCamera::OnBoxOverlap);

	//Get active PlayerController when game starts
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//StartTrigger->OnComponentEndOverlap.AddDynamic(this, &AGameStaticCamera::OnBoxEndOverlap);
}

void AGameStaticCamera::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Checks if overlapping object has Player tag
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		// Changes view if player overlaps
		ChangeCurrentCameraView();
	}
}

/**
* 
void AGameStaticCamera::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	return;
}

*/

void AGameStaticCamera::ChangeCurrentCameraView()
{
	// Changes camera view target to current camera
	PlayerController->SetViewTargetWithBlend(this);
}

void AGameStaticCamera::TargetLockOnPlayer()
{
	// Getting camera world location
	FVector CameraWorldLocation = GetCameraComponent()->GetComponentLocation();
	// Getting player world location
	FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();
	
	// Calculating rotation of the camera depending on player's position
	FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(CameraWorldLocation, PlayerLocation);

	//Setting camera component's rotation to a calculated value
	GetCameraComponent()->SetWorldRotation(LookRotation);

}

void AGameStaticCamera::BecomeViewTarget(APlayerController* PC)
{
	Super::BecomeViewTarget(PC);
	
	SetIsCameraActive();
}

void AGameStaticCamera::EndViewTarget(APlayerController* PC)
{
	Super::EndViewTarget(PC);

	SetIsCameraDisabled();

}
