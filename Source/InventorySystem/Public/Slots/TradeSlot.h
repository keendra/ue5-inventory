// Fill out your copyright notice in the Description page of Project Settings.

/**
 * UTradeSlot is a subclass of UBaseSlot, which represents a trade slot in an inventory system.
 * This class is used to handle trade transactions between players, by validating prerequisites and 
 * performing the necessary cost transfers.
 * 
 * @author Jóhanna Maj Landgren
 */

#pragma once

#include "CoreMinimal.h"
#include "Slots/InventorySlot.h"
#include "TradeSlot.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UTradeSlot : public UInventorySlot
{
	GENERATED_BODY()

public:
	/**
	 * Check the prerequisites for a trade transaction, where this UTradeSlot is the source slot.
	 * 
	 * @param Destination The destination slot of the trade transaction.
	 * @param Error The error code that occurred during the prerequisites check.
	 * 
	 * @return True if the prerequisites for the trade transaction are met, false otherwise.
	 */
	virtual bool CheckSourcePrerequisites(UBaseSlot* Destination, ETransferErrorCodes& Error) override;

	/**
	 * Check the prerequisites for a trade transaction, where this UTradeSlot is the destination slot.
	 * 
	 * @param Source The source slot of the trade transaction.
	 * @param Error The error code that occurred during the prerequisites check.
	 * 
	 * @return True if the prerequisites for the trade transaction are met, false otherwise.
	 */
	virtual bool CheckDestinationPrerequisites(UBaseSlot* Source, ETransferErrorCodes& Error) override;

	/**
	 * Perform any necessary actions for the trade transaction, when this UTradeSlot is the source slot.
	 * 
	 * @param Destination The destination slot of the trade transaction.
	 */
	virtual void PerformSourcePrerequisites(UBaseSlot* Destination) override;

	/**
	 * Perform any necessary actions for the trade transaction, when this UTradeSlot is the destination slot.
	 * 
	 * @param Source The source slot of the trade transaction.
	 */
	virtual void PerformDestinationPrerequisites(UBaseSlot* Source) override;

private:
	/**
	 * Validate the cost of a trade transaction.
	 *
	 * @param TradeSlot The source slot of the trade transaction.
	 * @param Buyer The owner of the source slot.
	 * @param Error The error code that occurred during the cost validation.
	 * 
	 * @return True if the buyer has sufficient resources to complete the trade, false otherwise.
	 */
	static bool ValidateCost(const UBaseSlot* TradeSlot, AActor* Buyer, ETransferErrorCodes& Error);
	
	/**
	 * Trade the cost of a trade transaction.
	 * 
	 * @param TradeSlot The source slot of the trade transaction.
	 * @param Trader The owner of the source slot.
	 * @param Modifier The value the price should be modified with, as well as if it's withdrawn or added (-/+).
	 * 
	 * @return True if the buyer has sufficient resources to complete the trade, false otherwise.
	 */
	static void TransferCost(const UBaseSlot* TradeSlot, AActor* Trader, float Modifier = -1);
};
