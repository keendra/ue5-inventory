// Fill out your copyright notice in the Description page of Project Settings.

#include "Slots/BaseSlot.h"

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

	Original->PerformPrerequisites(this);
	return true;
}

void UBaseSlot::Swap(UBaseSlot* Source)
{
	const UBaseSlot* Original = DuplicateObject(this, this->GetOuter());
	SetSlot(Source->Item, Source->Amount);
	Source->SetSlot(Original->Item, Original->Amount);
}

bool UBaseSlot::CheckPrerequisites(UBaseSlot* Other)
{
	return true;
}

void UBaseSlot::PerformPrerequisites(UBaseSlot* Other)
{
}

bool UBaseSlot::CheckTransferType(UBaseSlot* Source, ETransferType& Type, ETransferErrorCodes& Error)
{
	if(!Source->CheckPrerequisites(this))
	{
		Type = ETransferType::None;
		Error = ETransferErrorCodes::PrerequisiteInvalid;
		return false;
	}
	
	if(Item == nullptr)
	{
		Type = ETransferType::Move;
		Error = ETransferErrorCodes::None;
		return true;
	}
	if(IsSameType(Source->Item))
	{
		if(const int MaxSize = Source->Item->MaxStackSize; MaxSize == 0 || MaxSize > Source->Amount)
		{
			Type = ETransferType::Merge;
			Error = ETransferErrorCodes::None;
			return true;
		}
	}

	Type = ETransferType::Swap;
	Error = ETransferErrorCodes::None;
	return true;
}

bool UBaseSlot::IsSameType(const UBaseItem* SourceItem) const
{
	return SourceItem != nullptr && Item != nullptr ? SourceItem == Item : false;
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
