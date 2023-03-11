// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory.h"
#include "Slots/BaseSlot.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventory::BeginPlay()
{
	Super::BeginPlay();

	const int Size = AutoResize ? FMath::Max(InitialItems.Num(), BaseSize) : BaseSize;
	TArray<UBaseItem*> Items;
	InitialItems.GenerateKeyArray(Items);

	for (int SlotIndex = 0; SlotIndex < Size; ++SlotIndex)
	{
		UBaseSlot* Slot = NewObject<UBaseSlot>(this, SlotClass, "InventorySlot" + SlotIndex);
		if (Items.Num() > SlotIndex)
		{
			UBaseItem* Item = Items[SlotIndex];
			const int Amount = *InitialItems.Find(Item);
			Slot->SetSlot(Item, Amount);
		}
		Slots.Add(Slot);
	}
}

TArray<UBaseSlot*> UInventory::GetInventorySlots()
{
	return Slots;
}

TArray<UBaseSlot*> UInventory::GetSlotsWithItem(UBaseItem* Item) const
{
	return Slots.FilterByPredicate([Item](const UBaseSlot* Slot)
	{
		return Slot->IsSameType(Item);
	});
}

UBaseSlot* UInventory::GetEmptySlotForItem(UBaseItem* Item) const
{
	UBaseSlot* const * EmptySlot = Slots.FindByPredicate([](const UBaseSlot* Slot)
	{
		return Slot->Amount == 0;
	});

	if (*EmptySlot != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("GetSlotForItem - Found empty slot."));
		return *EmptySlot;
	}
    
	UE_LOG(LogTemp, Warning, TEXT("GetSlotForItem - No available slots."));
	return nullptr;
}

UBaseSlot* UInventory::GetSlotForItem(UBaseItem* Item) const
{
	UBaseSlot* const * ItemSlot = Slots.FindByPredicate([Item](const UBaseSlot* Slot)
	{
		return Slot->IsSameType(Item) && !Slot->IsFull();
	});

	if (*ItemSlot != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("GetSlotForItem - Found slot for item."));
		return *ItemSlot;
	}

	return GetEmptySlotForItem(Item);
}

bool UInventory::AddItem(UBaseItem* Item, const bool EmptyOnly) const
{
	if (UBaseSlot* AvailableSlot = EmptyOnly ? GetEmptySlotForItem(Item) : GetSlotForItem(Item);
		AvailableSlot != nullptr)
	{
		AvailableSlot->SetSlot(Item, AvailableSlot->Amount + 1);
		UE_LOG(LogTemp, Display, TEXT("Added item %s to slot"), *Item->GetName());
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("Failed to add item %s to inventory, no available slots"), *Item->GetName());
	return false;
}

bool UInventory::AddItems(UBaseItem* Item, const int Amount, const bool EmptyOnly) const
{
	/* TODO: This should validate first that there are enough slots if more than one is needed due to MaxAmount */
	for (int Count = 0; Count < Amount; Count++)
	{
		if(!AddItem(Item, EmptyOnly))
		{
			return false;
		}
	}

	return true;
}

TSoftObjectPtr<UTexture2D> UInventory::GetIcon() const
{
	return InventoryConfig == nullptr ? nullptr : InventoryConfig->Icon;
}
