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
	//=====================================
	// PARAMETERS & VARIABLES
	//=====================================



	//=====================================
	//	FUNCTIONS
	//=====================================

	AGameStaticCamera();

	virtual void Tick(float DeltaTime) override;

protected:

	//=====================================
	// PARAMETERS & VARIABLES
	//=====================================

	/**To check if chosen camera is a default one*/
	UPROPERTY(EditAnywhere, Category = "CameraSystem")
	bool bDefaultCamera = false;

	/**To check if current camera is used by PlayerController*/
	UPROPERTY(VisibleAnywhere, Category = "CameraSystem")
	bool bIsCameraActive = false;

	/**Specifies if camera should target on player or be static*/
	UPROPERTY(EditAnywhere, Category = "CameraSystem")
	bool bTargetOnPlayer = false;

	//=====================================
	//	FUNCTIONS
	//=====================================

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/**Activates camera*/
	FORCEINLINE void SetIsCameraActive() { bIsCameraActive = true; }
	/**Deactivates camera*/
	FORCEINLINE void SetIsCameraDisabled() { bIsCameraActive = false; }
	/**
	* @return If current camera is active or not
	*/
	FORCEINLINE bool GetIsCameraActive() { return bIsCameraActive; }

	/**
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	*/

	/**Changes camera view of PlayerController to another camera*/
	void ChangeCurrentCameraView();

	/**Lock target on Player Character; Rotates depending on player's position*/
	void TargetLockOnPlayer();

	virtual void BecomeViewTarget( APlayerController* PC) override;

	virtual void EndViewTarget( APlayerController* PC) override;

	/**Stores active PlayerController*/
	APlayerController* PlayerController;

private:

	//=====================================
	// PARAMETERS & VARIABLES
	//=====================================

	/**Box component representing activation trigger for camera to become an active camera view*/
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* StartTrigger;

	//=====================================
	//	FUNCTIONS
	//=====================================

};
