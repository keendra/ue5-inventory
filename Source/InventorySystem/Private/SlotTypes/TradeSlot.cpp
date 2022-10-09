// Fill out your copyright notice in the Description page of Project Settings.


#include "Slots/TradeSlot.h"

// TODO: If Source inventory (outer) is a different inventory.
// Get slot owner from outer (inventory), outer (actor)
// If same owner, item is just being moved around and this should return true
// If not, it's moved to a different owner and the inventory need to have the
//	required items (BaseItem->BasePrice) to perform this trade.
//	* Add a function in InventoryFunctionLibrary to look for the inventory
//		that contain the item and if it contain enough items.
//		* Note that in the future we might have implemented max stack size,
//			so this should at some point look for multiple slots if necessary
//		* Return true if enough items exists

bool UTradeSlot::CheckSourcePrerequisites(UBaseSlot* Source)
{
	// If item was moved from store to user (check can bought)
	UE_LOG(LogTemp, Warning, TEXT("Checking move from tradeslot"));
	return Super::CheckSourcePrerequisites(Source);
}

bool UTradeSlot::CheckDestinationPrerequisites(UBaseSlot* Destination)
{
	// If item was moved from user to store (check can sell)
	UE_LOG(LogTemp, Warning, TEXT("Checking move to tradeslot"));
	return Super::CheckDestinationPrerequisites(Destination);
}

void UTradeSlot::PerformSourcePrerequisites(UBaseSlot* Source)
{
	// Buy
	UE_LOG(LogTemp, Warning, TEXT("Performed Source Prerequisites"));
	return Super::PerformSourcePrerequisites(Source);
}

void UTradeSlot::PerformDestinationPrerequisites(UBaseSlot* Destination)
{
	// Sell
	UE_LOG(LogTemp, Warning, TEXT("Performed Destination Prerequisites"));
	return Super::PerformSourcePrerequisites(Destination);
}
