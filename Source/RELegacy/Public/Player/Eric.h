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
	//=====================================
	// PARAMETERS & VARIABLES
	//=====================================

	
	
	//=====================================
	//	FUNCTIONS
	//=====================================

	AEric();

	virtual void Tick(float DeltaTime) override;

	/** Function Part of EnhancedInput System, called to bind functionallity to input*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	//=====================================
	// PARAMETERS & VARIABLES
	//=====================================

	/**	Enhanced input action variables */
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> GContext;

	/** 
	*	Data Config of Action mappings for Enhanced Input System
	*	Allows to specify action mappings in a separate data config blueprint and not in the character class directly
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	TObjectPtr<UInputDataConfig> InputActions;


	//=====================================
	//	FUNCTIONS
	//=====================================

	virtual void BeginPlay() override;

	/** 
	*	Function moves chatarter in 3D space depending on a certain 2D value.
	*	@param Value : This is value of WASD (or other specified) movement input in 2D space; 
	*/
	void Move(const FInputActionValue& Value);

	/**
	*	Function moves camera look in 3D space depending on a certain 2D value.
	*	@param Value : This is value of mouse movement input in 2D space;
	*/
	void Look(const FInputActionValue& Value);

	/** Interaction with objects, depends on action mapping input (if button pressed or not) */
	void Interact();

	/**
	*	Sets the item that currently overlapes with Sphere component.
	*	@param Item : Item Actor overlapping with the Sphere component;
	*/
	virtual void SetOverlappingItem(AItem* Item);


private:	

	//=====================================
	// PARAMETERS & VARIABLES
	//=====================================	
	 
	/** Camera boom positioning camera behind player character*/
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> PlayerCamera;

	/** Sphere collision area*/
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>  Sphere;

	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<AItem> OverlappingItem;


	//=====================================
	//	FUNCTIONS
	//=====================================

};
