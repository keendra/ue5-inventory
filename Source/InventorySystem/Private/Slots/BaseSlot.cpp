// Fill out your copyright notice in the Description page of Project Settings.

#include "Slots/BaseSlot.h"

#include "Inventory.h"

DEFINE_LOG_CATEGORY(LogInventory);

bool UBaseSlot::TryTransfer(UBaseSlot* Source, ETransferErrorCodes& Error)
{	
	ETransferType TransferType;
	if(!CheckTransferType(Source, TransferType, Error))
	{
		return false;
	}

	UBaseSlot* Original = DuplicateObject(Source, Source->GetOuter());
	switch (TransferType)
	{
	case ETransferType::Move:
	case ETransferType::Merge:
		MergeAll(Source, Error);
		break;
	case ETransferType::Swap:
		Swap(Source);
		break;
	case ETransferType::None:
	default:
		return false;
	}

	Original->PerformSourcePrerequisites(this);
	this->PerformDestinationPrerequisites(Original);
	return true;
}

bool UBaseSlot::TrySplit(int SplitAmount, ETransferErrorCodes& Error)
{
	const UInventory* Inventory = Cast<UInventory>(this->GetOuter());
	if(Inventory->AddItems(Item, SplitAmount, true))
	{
		UE_LOG(LogInventory, Error, TEXT("Did this"));
		ChangeAmount(-SplitAmount);
		return true;
	}

	UE_LOG(LogInventory, Error, TEXT("Did fail this"));
	return false;
}

void UBaseSlot::Swap(UBaseSlot* Source)
{
	const UBaseSlot* Original = DuplicateObject(this, this->GetOuter());
	SetSlot(Source->Item, Source->Amount);
	Source->SetSlot(Original->Item, Original->Amount);
}

bool UBaseSlot::CheckDestinationPrerequisites(UBaseSlot* Other, ETransferErrorCodes& Error)
{
	return true;
}

bool UBaseSlot::CheckSourcePrerequisites(UBaseSlot* Other, ETransferErrorCodes& Error)
{
	return true;
}

void UBaseSlot::PerformDestinationPrerequisites(UBaseSlot* Other)
{
}

void UBaseSlot::PerformSourcePrerequisites(UBaseSlot* Other)
{
}

bool UBaseSlot::IsEmpty() const
{
	return Amount == 0;
}

bool UBaseSlot::IsFull() const
{
	const int MaxSize = Item->MaxStackSize;
	return MaxSize != 0 && MaxSize <= Amount;
}

bool UBaseSlot::CheckTransferType(UBaseSlot* Source, ETransferType& Type, ETransferErrorCodes& Error)
{	
	if(this == Source || !Source->CheckSourcePrerequisites(this, Error) || !this->CheckDestinationPrerequisites(Source, Error))
	{
		return false;
	}
	
	if(Item == nullptr)
	{
		Type = ETransferType::Move;
		return true;
	}
	if(IsSameType(Source->Item))
	{
		if(const int MaxSize = Source->Item->MaxStackSize; MaxSize == 0 || MaxSize > Source->Amount)
		{
			Type = ETransferType::Merge;
			return true;
		}
	}

	Type = ETransferType::Swap;
	return true;
}

bool UBaseSlot::IsSameType(const UBaseItem* SourceItem) const
{
	return SourceItem != nullptr && Item != nullptr ? SourceItem == Item : false;
}

bool UBaseSlot::IsSameOwner(const UBaseSlot* Other) const
{
	const AActor* Owner = Cast<AActor>(this->GetOuter()->GetOuter());
	const AActor* OtherOwner = Cast<AActor>(Other->GetOuter()->GetOuter());

	return Owner == OtherOwner;
}

bool UBaseSlot::MergeAll(UBaseSlot* Source, ETransferErrorCodes& Error)
{
	const int MaxSize = Source->Item->MaxStackSize;
	const int Total = Amount + Source->Amount;

	if (Total > MaxSize && MaxSize > 0) 
	{
		UE_LOG(LogInventory, Error, TEXT("Overflow occurred while merging items, MaxStackSize is %d but %d items are being merged"), MaxSize, Total);
		// An overflow would occur, set the Error parameter accordingly
		Error = ETransferErrorCodes::Overflow;
		return false;
	}
	
	const int DestinationAmount = MaxSize > 0 ? FMath::Min(Total, MaxSize) : Total;
	const int SourceAmount = MaxSize > 0 ? FMath::Max(0, Total - MaxSize) : 0;
	SetSlot(Source->Item, DestinationAmount);
	Source->SetSlot(Source->Item, SourceAmount);
	return true;
}

void UBaseSlot::SetSlot(UBaseItem* NewItem, const int NewAmount)
{
	this->Item = NewItem;
	this->Amount = NewAmount;
	OnSlotUpdatedDelegate.Broadcast(this);
}

bool UBaseSlot::ChangeAmount(const int DiffAmount)
{
	if (Amount + DiffAmount < 0)
	{
		return false;
	}
	
	this->Amount = Amount += DiffAmount;
	OnSlotUpdatedDelegate.Broadcast(this);
	return true;
}
