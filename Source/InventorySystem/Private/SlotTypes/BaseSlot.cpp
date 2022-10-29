// Fill out your copyright notice in the Description page of Project Settings.

#include "Slots/BaseSlot.h"

#include "IntVectorTypes.h"
#include "../../../Plugins/Developer/RiderLink/Source/RD/thirdparty/spdlog/include/spdlog/fmt/bundled/format.h"

bool UBaseSlot::TryTransfer(UBaseSlot* Source)
{
	ETransferType TransferType;
	ETransferErrorCodes ErrorCode;
	if(!CheckTransferType(Source, TransferType, ErrorCode))
	{
		return false;
	}

	UBaseSlot* Original = DuplicateObject(Source, Source->GetOuter());
	switch (TransferType)
	{
	case ETransferType::Merge:
		MergeAll(Source);
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
	
	if(IsSameType(Source->Item))
	{
		if(const int MaxSize = Source->Item->MaxStackSize; MaxSize == 0 || MaxSize > Source->Amount)
		{
			Type = ETransferType::Merge;
			Error = ETransferErrorCodes::PrerequisiteInvalid;
			return true;
		}
	}

	Type = ETransferType::Swap;
	Error = ETransferErrorCodes::PrerequisiteInvalid;
	return true;
}

bool UBaseSlot::IsSameType(const UBaseItem* SourceItem) const
{
	return SourceItem != nullptr && Item != nullptr ? SourceItem == Item : false;
}

void UBaseSlot::MergeAll(UBaseSlot* Source)
{
	const int MaxSize = Source->Item->MaxStackSize;
	const int Total = Amount + Source->Amount;
	const int DestinationAmount = MaxSize > 0 ? FMath::Min(Total, MaxSize) : Total;
	const int SourceAmount = MaxSize > 0 ? FMath::Max(0, Total - MaxSize) : 0;
	SetSlot(Source->Item, DestinationAmount);
	Source->SetSlot(Source->Item, SourceAmount);
}

void UBaseSlot::SetSlot(UBaseItem* NewItem, const int NewAmount)
{
	this->Item = NewItem;
	this->Amount = NewAmount;
	OnSlotUpdated.Broadcast();
}
