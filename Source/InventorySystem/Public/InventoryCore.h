// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slots/BaseSlot.h"
#include "InventorySettings.h"
#include "Components/ActorComponent.h"
#include "Slots/InventorySlot.h"
#include "InventoryCore.generated.h"

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
class INVENTORYSYSTEM_API UInventoryCore : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryCore();

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
	 * @param FilterFullSlots
	 * @param AllowEmptySlots
	 *
	 * @return An array of UBaseSlot pointers that contain the specified item
	 *
	 * @see UBaseSlot
	 * @see UBaseItem
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	TArray<UBaseSlot*> GetSlotsWithItem(UBaseItem* Item) const;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	UBaseSlot* GetEmptySlotForItem(UBaseItem* Item) const;

	/**
	 * Searches for a slot that can hold the specified item.
	 * 
	 * @param Item The item to find a slot for.
	 * @return A pointer to a slot that can hold the item, or nullptr if no slot is available.
	 *
	 * @see UBaseItem
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	UBaseSlot* GetSlotForItem(UBaseItem* Item) const;

	/**
	 * Adds an item to the inventory.
	 * 
	 * @param Item The item to add.
	 * @param EmptyOnly
	 * @return True if the item was successfully added, false otherwise.
	 *
	 * @see UBaseItem
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
    bool AddItem(UBaseItem* Item, bool EmptyOnly = false) const;

	/**
	 * Adds multiple items to the inventory.
	 * @param Item The item to add.
	 * @param Amount The number of items to add.
	 *
	 * @see UBaseItem
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool AddItems(UBaseItem* Item, int Amount = 1, bool EmptyOnly = false) const;

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
	UPROPERTY()
	TArray<UBaseSlot*> Slots;	
};
