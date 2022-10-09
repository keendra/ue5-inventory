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