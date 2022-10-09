// Fill out your copyright notice in the Description page of Project Settings.


#include "Slots/InventorySlot.h"

void UInventorySlot::SetSlot(UBaseItem* NewItem, int NewAmount)
{
	Super::SetSlot(NewItem, NewAmount > 0 ? NewAmount : 1);
}