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
	return Slots.FilterByPredicate([Item](const UBaseSlot* InventorySlot)
	{
		return InventorySlot->IsSameType(Item);
	});
}

TSoftObjectPtr<UTexture2D> UInventory::GetIcon() const
{
	return InventoryConfig == nullptr ? nullptr : InventoryConfig->Icon;
}
