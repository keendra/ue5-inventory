// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slots/BaseSlot.h"
#include "InventorySettings.h"
#include "Components/ActorComponent.h"
#include "Slots/InventorySlot.h"
#include "Inventory.generated.h"

/**
 * UInventory is a component class that represents an in-game inventory system. It contains a list of inventory slots,
 * each of which holds a specific item and its corresponding amount. 
 *
 * The inventory's properties can be set through the Unreal Engine Editor, including the base size, maximum weight,
 * auto resize toggle, and initial items. Additionally, the class provides functions to retrieve the entire inventory
 * or specific slots that hold a certain item.
 *
 * @see UBaseSlot
 * @see UInventorySettings
 * @see UBaseItem
 */
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventory();

	/** The base size of the inventory */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	int BaseSize;

	/** The maximum weight the inventory can carry */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	float MaxWeight;

	/** A toggle that determines whether the inventory should automatically resize to accommodate its items */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	bool AutoResize;

	/** The class of slot to use in this inventory */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	TSubclassOf<UBaseSlot> SlotClass = UInventorySlot::StaticClass();

	/** A map of initial items to add to the inventory */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	TMap<UBaseItem*, int> InitialItems;

	/** A pointer to the inventory settings */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	UInventorySettings* InventoryConfig;

	/**
	 * Retrieves the entire list of inventory slots in the UInventory object
	 *
	 * @return An array of UBaseSlot pointers
	 *
	 * @see UBaseSlot
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	TArray<UBaseSlot*> GetInventorySlots();

	/**
	 * Retrieves all inventory slots that contain the specified item
	 *
	 * @param Item The item to search for
	 *
	 * @return An array of UBaseSlot pointers that contain the specified item
	 *
	 * @see UBaseSlot
	 * @see UBaseItem
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	TArray<UBaseSlot*> GetSlotsWithItem(UBaseItem* Item) const;

	/**
	 * Retrieves the icon texture for the inventory
	 *
	 * @return A TSoftObjectPtr to a UTexture2D object
	 *
	 * @see UTexture2D
	 * @see TSoftObjectPtr
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	TSoftObjectPtr<UTexture2D> GetIcon() const;

protected:
	virtual void BeginPlay() override;

private:
	TArray<UBaseSlot*> Slots;	
};
