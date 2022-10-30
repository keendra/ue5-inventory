// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Items/BaseItem.h"
#include "BaseSlot.generated.h"

UENUM(BlueprintType)
enum class ETransferErrorCodes : uint8
{
	None,
	PrerequisiteInvalid
};

UENUM(BlueprintType)
enum class ETransferType : uint8
{
	None,
	Merge,
	Swap,
	Move,
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSlotUpdated);

/**
 * 
 */
UCLASS(Blueprintable)
class INVENTORYSYSTEM_API UBaseSlot : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Inventory System")
	bool TryTransfer(UBaseSlot* Source, ETransferErrorCodes& Error);
	
	UFUNCTION(BlueprintCallable, Category="Inventory System")
	void Swap(UBaseSlot* Source);

	UFUNCTION(BlueprintCallable, Category="Inventory System")
	virtual bool CheckPrerequisites(UBaseSlot* Other);

	UFUNCTION(BlueprintCallable, Category="Inventory System")
	virtual void PerformPrerequisites(UBaseSlot* Other);

	UFUNCTION(BlueprintCallable, Category="Inventory System")
	bool CheckTransferType(UBaseSlot* Source, ETransferType& Type, ETransferErrorCodes& Error);

	virtual void SetSlot(UBaseItem* NewItem, int NewAmount);

	bool IsSameType(const UBaseItem* SourceItem) const;

	UPROPERTY(BlueprintAssignable, Category = "Inventory System")
	FSlotUpdated OnSlotUpdated;

	[[nodiscard]] int GetAmount() const
	{
		return Amount;
	}

	[[nodiscard]] UBaseItem* GetItem() const
	{
		return Item;
	}
protected:
	UPROPERTY(BlueprintReadWrite, Category="Inventory System")
	UBaseItem* Item;
protected:
	UPROPERTY(BlueprintReadWrite, Category="Inventory System")
	int Amount;

private:
	void MergeAll(UBaseSlot* Source);
};
