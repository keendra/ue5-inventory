// Fill out your copyright notice in the Description page of Project Settings.


#include "Slots/TradeSlot.h"
#include "InventoryFunctionLibrary.h"

bool UTradeSlot::CheckPrerequisites(UBaseSlot* Other)
{
	if (!Super::CheckPrerequisites(Other))
	{
		return false;
	}
	AActor* Owner = Cast<AActor>(this->GetOuter()->GetOuter());
	AActor* OtherOwner = Cast<AActor>(Other->GetOuter()->GetOuter());

	if(Owner == OtherOwner)
	{
		return true;
	}

	for (const TTuple<UBaseItem*, int> Price : Item->BasePrice)
	{
		const int TotalAmount = Price.Value * Amount;
		if (const int OwnedAmount = UInventoryFunctionLibrary::GetOwnItemAmount(OtherOwner, Price.Key);
			TotalAmount > OwnedAmount)
		{
			return false;
		}
	}
	
	return true;
}

void UTradeSlot::PerformPrerequisites(UBaseSlot* Other)
{
	UE_LOG(LogTemp, Warning, TEXT("Performed Source Prerequisites"));
	Super::PerformPrerequisites(Other);
	AActor* OtherOwner = Cast<AActor>(Other->GetOuter()->GetOuter());
	
	for (const TTuple<UBaseItem*, int> Price : Item->BasePrice)
	{
		TArray<UBaseSlot*> ItemSlots = UInventoryFunctionLibrary::GetSlotsWithItem(OtherOwner, Price.Key);
		int RemainingPrice = Price.Value * Amount;
		for (UBaseSlot* ItemSlot : ItemSlots)
		{
			const int WithdrawAmount = FMath::Min(RemainingPrice, ItemSlot->GetAmount());
			ItemSlot->SetSlot(Price.Key, ItemSlot->GetAmount() - WithdrawAmount);
			RemainingPrice -= WithdrawAmount;

			if (RemainingPrice == 0)
			{
				return;
			}
		}
	}
}
