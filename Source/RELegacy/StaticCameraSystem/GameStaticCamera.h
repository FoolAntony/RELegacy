// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "GameStaticCamera.generated.h"


class UBoxComponent;

UCLASS()
class RELEGACY_API AGameStaticCamera : public ACameraActor
{
	GENERATED_BODY()

public:

	AGameStaticCamera();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "CameraSystem")
	bool bDefaultCamera = false;

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ChangeCurrentCameraView(AActor* CameraActor);

private:

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* StartTrigger;
	
};
