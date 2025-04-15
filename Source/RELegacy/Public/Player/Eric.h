// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Eric.generated.h"

class UInputDataConfig;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;

UCLASS()

class RELEGACY_API AEric : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEric();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();

	/**	Enhanced input action variables */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* GContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputDataConfig* InputActions;

private:	

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* PlayerCamera;

};
