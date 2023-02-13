// Fill out your copyright notice in the Description page of Project Settings.


#include "Slots/TradeSlot.h"
#include "InventoryFunctionLibrary.h"

bool UTradeSlot::CheckSourcePrerequisites(UBaseSlot* Destination, ETransferErrorCodes& Error)
{
	UE_LOG(LogTemp, Warning, TEXT("Check Source Prerequisites"));
	AActor* OtherOwner = Cast<AActor>(Destination->GetOuter()->GetOuter());
	return Super::CheckDestinationPrerequisites(Destination, Error) && (IsSameOwner(Destination) || ValidateCost(this, OtherOwner, Error));
}

bool UTradeSlot::CheckDestinationPrerequisites(UBaseSlot* Source, ETransferErrorCodes& Error)
{
	UE_LOG(LogTemp, Warning, TEXT("Check Destination Prerequisites"));
	AActor* Owner = Cast<AActor>(GetOuter()->GetOuter());
	return Super::CheckDestinationPrerequisites(Source, Error) && (IsSameOwner(Source) || ValidateCost(Source, Owner, Error));
}

void UTradeSlot::PerformDestinationPrerequisites(UBaseSlot* Source)
{
	UE_LOG(LogTemp, Warning, TEXT("Performed Destination Prerequisites"));
	Super::PerformDestinationPrerequisites(Source);
	AActor* Buyer = Cast<AActor>(GetOuter()->GetOuter());
	AActor* Seller = Cast<AActor>(Source->GetOuter()->GetOuter());

	if (!IsSameOwner(Source))
	{
		TransferCost(Source, Buyer, -1);	// Withdraw cost from buyer
		TransferCost(Source, Seller, 1);	// Add cost to seller
	}
}

void UTradeSlot::PerformSourcePrerequisites(UBaseSlot* Destination)
{
	UE_LOG(LogTemp, Warning, TEXT("Performed Source Prerequisites"));
	Super::PerformSourcePrerequisites(Destination);
	AActor* Seller = Cast<AActor>(GetOuter()->GetOuter());
	AActor* Buyer = Cast<AActor>(Destination->GetOuter()->GetOuter());
	if (!IsSameOwner(Destination))
	{
		TransferCost(this, Buyer, -1);	// Withdraw cost from buyer
		TransferCost(this, Seller, 1);	// Add cost to seller
	}
}

bool UTradeSlot::ValidateCost(const UBaseSlot* TradeSlot, AActor* Buyer, ETransferErrorCodes& Error)
{
	for (const TTuple<UBaseItem*, int> Price : TradeSlot->GetItem()->BasePrice)
	{
		const int TotalAmount = Price.Value * TradeSlot->GetAmount();
		if (const int OwnedAmount = UInventoryFunctionLibrary::GetOwnItemAmount(Buyer, Price.Key);
			TotalAmount > OwnedAmount)
		{
			Error = ETransferErrorCodes::InsufficientAmount;
			const FString ItemName = Price.Key->GetName();
			UE_LOG(LogTemp, Warning, TEXT("ValidateCost failed: OwnedAmount %d, TotalAmount %d, UBaseItem %s"), OwnedAmount, TotalAmount, *ItemName);
			return false;
		}
	}
	
	return true;
}

void UTradeSlot::TransferCost(const UBaseSlot* TradeSlot, AActor* Trader, const float Modifier)
{
	const int Direction = Modifier < 0 ? -1 : 1;
	for (const TTuple<UBaseItem*, int> Price : TradeSlot->GetItem()->BasePrice)
	{
		TArray<UBaseSlot*> ItemSlots = UInventoryFunctionLibrary::GetSlotsWithItem(Trader, Price.Key);
		float Remaining = Price.Value * TradeSlot->GetAmount() * FMath::Abs(Modifier);
		for (UBaseSlot* ItemSlot : ItemSlots)
		{
			const float Change = Direction < 0 ? FMath::Max(Remaining, ItemSlot->GetAmount()) : Remaining;
			ItemSlot->SetSlot(Price.Key, ItemSlot->GetAmount() + Remaining * Direction);
			Remaining -= Change;

			if (Remaining == 0)
			{
				return;
			}
		}
	}
}
