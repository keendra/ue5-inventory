// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Items/BaseItem.h"
#include "BaseSlot.generated.h"

UENUM()
enum class ETransferErrorCodes
{
	None,
	ListInvalid,
	MoveInvalid,
	PrerequisiteInvalid
};

UENUM()
enum class ETransferType
{
	None,
	Merge,
	Swap
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
	bool TryTransfer(UBaseSlot* Source);
	
	UFUNCTION(BlueprintCallable, Category="Inventory System")
	void Swap(UBaseSlot* Source);

	UFUNCTION(BlueprintCallable, Category="Inventory System")
	virtual bool CheckSourcePrerequisites(UBaseSlot* Source);

	UFUNCTION(BlueprintCallable, Category="Inventory System")
	virtual bool CheckDestinationPrerequisites(UBaseSlot* Destination);

	UFUNCTION(BlueprintCallable, Category="Inventory System")
	virtual void PerformSourcePrerequisites(UBaseSlot* Source);

	UFUNCTION(BlueprintCallable, Category="Inventory System")
	virtual void PerformDestinationPrerequisites(UBaseSlot* Destination);

	UFUNCTION(BlueprintCallable, Category="Inventory System")
	bool CheckTransferType(UBaseSlot* Source, ETransferType& Type, ETransferErrorCodes& Error);

	virtual void SetSlot(UBaseItem* NewItem, int NewAmount);

	UPROPERTY(BlueprintAssignable, Category = "Inventory System")
	FSlotUpdated OnSlotUpdated;
protected:
	UPROPERTY(BlueprintReadWrite, Category="Inventory System")
	UBaseItem* Item;

	UPROPERTY(BlueprintReadWrite, Category="Inventory System")
	int Amount;
private:
	bool IsSameType(const UBaseItem* SourceItem) const;

	void MergeAll(UBaseSlot* Source);
};
