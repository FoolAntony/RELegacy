// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStaticCamera.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

AGameStaticCamera::AGameStaticCamera() 
{
	StartTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Start Trigger"));
	StartTrigger->SetupAttachment(GetRootComponent());

	StartTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StartTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

}

void AGameStaticCamera::BeginPlay()
{
	Super::BeginPlay();

	StartTrigger->OnComponentBeginOverlap.AddDynamic(this, &AGameStaticCamera::OnBoxOverlap);
	StartTrigger->OnComponentEndOverlap.AddDynamic(this, &AGameStaticCamera::OnBoxEndOverlap);
}

void AGameStaticCamera::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		ChangeCurrentCameraView(OtherActor);
	}
}

void AGameStaticCamera::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	return;
}

void AGameStaticCamera::ChangeCurrentCameraView(AActor* OverlappingActor)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetViewTargetWithBlend(this);
}
