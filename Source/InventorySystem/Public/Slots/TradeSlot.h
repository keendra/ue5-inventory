// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slots/InventorySlot.h"
#include "TradeSlot.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UTradeSlot : public UInventorySlot
{
	GENERATED_BODY()

public:
	virtual bool CheckPrerequisites(UBaseSlot* Other) override;
	virtual void PerformPrerequisites(UBaseSlot* Other) override;
};
