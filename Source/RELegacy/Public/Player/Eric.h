// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/SphereComponent.h"
#include "Interfaces/PickupInterface.h"
#include "Eric.generated.h"

class UInputMappingContext;
class UInputDataConfig;
class USpringArmComponent;
class UCameraComponent;
class USphereComponent;

UCLASS()

class RELEGACY_API AEric : public ACharacter, public IPickupInterface
{
	GENERATED_BODY()

public:
	AEric();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();
	virtual void SetOverlappingItem(AItem* Item);

	/**	Enhanced input action variables */
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> GContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	TObjectPtr<UInputDataConfig> InputActions;

private:	

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> PlayerCamera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>  Sphere;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

};
