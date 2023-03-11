// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSlot.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInventorySlot : public UBaseSlot
{
	GENERATED_BODY()
public:
	virtual void SetSlot(UBaseItem* NewItem, int NewAmount) override;

	virtual bool ChangeAmount(int DiffAmount) override;
};
