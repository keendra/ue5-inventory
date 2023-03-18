// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryFunctionLibrary.h"

TArray<UInventoryCore*> UInventoryFunctionLibrary::GetVisibleInventories(AActor* Actor)
{
	TArray<UInventoryCore*> Components;
	Actor->GetComponents<UInventoryCore>(Components);

	return Components.FilterByPredicate([](const UInventoryCore* Inventory)
		{
			if (Inventory->InventoryConfig == nullptr)
			{
				return Cast<UInventorySettings>(UInventorySettings::StaticClass()->GetDefaultObject(true))->Show;
			}

			return Inventory->InventoryConfig->Show;
	});
}

UInventoryCore* UInventoryFunctionLibrary::GetInventory(AActor* Actor, UBaseItem* Item)
{
	TArray<UInventoryCore*> Components;
	Actor->GetComponents<UInventoryCore>(Components);

	return *Components.FindByPredicate([Item](const UInventoryCore* Inventory)
		{
			return Inventory->InventoryConfig == nullptr
				|| Inventory->InventoryConfig->ParentType == nullptr
				|| Item->GetClass()->IsChildOf(Inventory->InventoryConfig->ParentType);
	});
}

TArray<UBaseSlot*> UInventoryFunctionLibrary::GetSlotsWithItem(AActor* Actor, UBaseItem* Item)
{
	TArray<UInventoryCore*> Components;
	Actor->GetComponents<UInventoryCore>(Components);

	TArray<UBaseSlot*> Result;

	for (const UInventoryCore* Inventory : Components)
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
