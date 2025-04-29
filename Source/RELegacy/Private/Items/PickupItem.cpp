// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickupItem.h"

APickupItem::APickupItem()
{
}

void APickupItem::Interact()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, TEXT("Item picked up!"));
	Destroy();
}





