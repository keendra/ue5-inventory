// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryFunctionLibrary.h"

TArray<UInventory*> UInventoryFunctionLibrary::GetVisibleInventories(AActor* Actor)
{
	TArray<UInventory*> Components;
	Actor->GetComponents<UInventory>(Components);

	return Components.FilterByPredicate([](const UInventory* Inventory)
		{
			if (Inventory->InventoryConfig == nullptr)
			{
				return Cast<UInventorySettings>(UInventorySettings::StaticClass()->GetDefaultObject(true))->Show;
			}

			return Inventory->InventoryConfig->Show;
	});
}

UInventory* UInventoryFunctionLibrary::GetInventory(AActor* Actor, UBaseItem* Item)
{
	TArray<UInventory*> Components;
	Actor->GetComponents<UInventory>(Components);

	return *Components.FindByPredicate([Item](const UInventory* Inventory)
		{
			return Inventory->InventoryConfig == nullptr
				|| Inventory->InventoryConfig->ParentType == nullptr
				|| Item->GetClass()->IsChildOf(Inventory->InventoryConfig->ParentType);
	});
}

TArray<UBaseSlot*> UInventoryFunctionLibrary::GetSlotsWithItem(AActor* Actor, UBaseItem* Item)
{
	TArray<UInventory*> Components;
	Actor->GetComponents<UInventory>(Components);

	TArray<UBaseSlot*> Result;

	for (const UInventory* Inventory : Components)
	{
		Result.Append(Inventory->GetSlotsWithItem(Item));
	}

	return Result;
}

int UInventoryFunctionLibrary::GetOwnItemAmount(AActor* Actor, UBaseItem* Item)
{
	TArray<UBaseSlot*> OwnedInSlots = GetSlotsWithItem(Actor, Item);
	int Amount = 0;

	for (const UBaseSlot* Slot : OwnedInSlots)
	{
		Amount += Slot->Amount;
	}

	return Amount;
}
