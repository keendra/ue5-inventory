// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Items/BaseItem.h"
#include "Logging/LogCategory.h"
#include "BaseSlot.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogInventory, Log, All);

/*
 * @enum ETransferErrorCodes
 * Enum that represents the error codes for a transfer between two slots.
 */
UENUM(BlueprintType)
enum class ETransferErrorCodes : uint8
{
	None,
	PrerequisiteInvalid,
	Overflow
};

/*
 * @enum ETransferType
 * Enum that represents the type of transfer that can be performed between two slots.
 */
UENUM(BlueprintType)
enum class ETransferType : uint8
{
	None,
	Merge,
	Swap,
	Move,
};

// Forward declaration for UBaseSlot
class UBaseSlot;

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSlotUpdated, UBaseSlot*, Slot);

/**
 * UBaseSlot
 * This class represents a slot in an inventory system for Unreal Engine 5. The class implements the basic functionality
 * for a slot, such as holding items, swapping items with other slots, and merging items with other slots if they are of
 * the same type. The class also provides methods to check if a transfer is possible between two slots and to perform the
 * necessary prerequisites before a transfer.
 *
 * @summary This class represents a slot in an inventory system for Unreal Engine 5.
 */
UCLASS(Blueprintable)
class INVENTORYSYSTEM_API UBaseSlot : public UObject
{
	GENERATED_BODY()

public:
	/*
	 * @function TryTransfer
	 * Tries to transfer items between two slots.
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory System")
	bool TryTransfer(UBaseSlot* Source, ETransferErrorCodes& Error);

	/*
	 * @function Swap
	 * Swaps items between two slots.
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory System")
	void Swap(UBaseSlot* Source);

	/*
	 * @function CheckPrerequisites
	 * Checks if the prerequisites for a transfer between two slots are met.
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory System")
	virtual bool CheckPrerequisites(UBaseSlot* Other);

	/*
	* @function PerformPrerequisites
	* Performs the prerequisites for a transfer between two slots.
	*/
	UFUNCTION(BlueprintCallable, Category="Inventory System")
	virtual void PerformPrerequisites(UBaseSlot* Other);

	/*
	* @function CheckTransferType
	* Checks the type of transfer that can be performed between two slots.
	*/
	UFUNCTION(BlueprintCallable, Category="Inventory System")
	bool CheckTransferType(UBaseSlot* Source, ETransferType& Type, ETransferErrorCodes& Error);

	/*
	* @function SetSlot
	* Sets the item and amount for a slot.
	*/
	virtual void SetSlot(UBaseItem* NewItem, int NewAmount);

	/*
	 * @function IsSameType
	 * Checks if two items are of the same type.
	 */
	bool IsSameType(const UBaseItem* SourceItem) const;

	/*
	 * @property OnSlotUpdatedDelegate
	 * A delegate that is broadcasted when the slot is updated.
	 */
	UPROPERTY(BlueprintAssignable, Category = "Inventory System")
	FSlotUpdated OnSlotUpdatedDelegate;

	[[nodiscard]] int GetAmount() const
	{
		return Amount;
	}

	[[nodiscard]] UBaseItem* GetItem() const
	{
		return Item;
	}
protected:
	/*
	 * @property Item
	 * A pointer to the item held by the slot.
	 */
	UPROPERTY(BlueprintReadWrite, Category="Inventory System")
	UBaseItem* Item;

	/*
	 * @property Amount
	 * The amount of items held by the slot.
	 */
	UPROPERTY(BlueprintReadWrite, Category="Inventory System")
	int Amount;

private:
	bool MergeAll(UBaseSlot* Source, ETransferErrorCodes& Error);
};
