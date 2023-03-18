// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InventoryCore.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "InventoryFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInventoryFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Inventory)
	static TArray<UInventoryCore*> GetVisibleInventories(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	static UInventoryCore* GetInventory(AActor* Actor, UBaseItem* Item);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	static TArray<UBaseSlot*> GetSlotsWithItem(AActor* Actor, UBaseItem* Item);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	static int GetOwnItemAmount(AActor* Actor, UBaseItem* Item);
};
