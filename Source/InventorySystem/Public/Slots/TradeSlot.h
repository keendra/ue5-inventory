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
	virtual bool CheckSourcePrerequisites(UBaseSlot* Source) override;
	virtual bool CheckDestinationPrerequisites(UBaseSlot* Destination) override;
	virtual void PerformSourcePrerequisites(UBaseSlot* Source) override;
	virtual void PerformDestinationPrerequisites(UBaseSlot* Destination) override;
};
