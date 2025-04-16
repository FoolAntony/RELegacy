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

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;



	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "CameraSystem")
	bool bDefaultCamera = false;
	
	UPROPERTY(VisibleAnywhere, Category = "CameraSystem")
	bool bIsCameraActive = false;

	UPROPERTY(EditAnywhere, Category = "CameraSystem")
	bool bTargetOnPlayer = false;

	FORCEINLINE void SetIsCameraActive() { bIsCameraActive = true; }
	FORCEINLINE void SetIsCameraDisabled() { bIsCameraActive = false; }
	FORCEINLINE bool GetIsCameraActive() { return bIsCameraActive; }

	/**
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	*/
	void ChangeCurrentCameraView();

	void TargetLockOnPlayer();

	virtual void BecomeViewTarget( APlayerController* PC) override;

	virtual void EndViewTarget( APlayerController* PC) override;

	APlayerController* PlayerController;

private:

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* StartTrigger;



};
