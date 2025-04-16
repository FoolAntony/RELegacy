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

	StartTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Start Trigger"));
	StartTrigger->SetupAttachment(GetRootComponent());

	StartTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StartTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

}

void AGameStaticCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTargetOnPlayer && GetIsCameraActive())
	{
		TargetLockOnPlayer();
	}
}

void AGameStaticCamera::BeginPlay()
{
	Super::BeginPlay();

	StartTrigger->OnComponentBeginOverlap.AddDynamic(this, &AGameStaticCamera::OnBoxOverlap);
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//StartTrigger->OnComponentEndOverlap.AddDynamic(this, &AGameStaticCamera::OnBoxEndOverlap);
}

void AGameStaticCamera::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
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

	PlayerController->SetViewTargetWithBlend(this);
}

void AGameStaticCamera::TargetLockOnPlayer()
{

	FVector CameraWorldLocation = GetCameraComponent()->GetComponentLocation();
	FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();

	FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(CameraWorldLocation, PlayerLocation);

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
