// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "PickupItem.generated.h"

class UNiagaraComponent;

UCLASS()
class RELEGACY_API APickupItem : public AItem
{
	GENERATED_BODY()

public:

	APickupItem();

	virtual void Interact() override;


	
};
