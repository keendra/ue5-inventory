// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slots/BaseSlot.h"
#include "InventorySettings.h"
#include "Components/ActorComponent.h"
#include "Slots/InventorySlot.h"
#include "Inventory.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventory();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	int BaseSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	float MaxWeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	bool AutoResize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	TSubclassOf<UBaseSlot> SlotClass = UInventorySlot::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	TMap<UBaseItem*, int> InitialItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	UInventorySettings* InventoryConfig;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	TArray<UBaseSlot*> GetInventorySlots();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	TArray<UBaseSlot*> GetSlotsWithItem(UBaseItem* Item) const;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	TSoftObjectPtr<UTexture2D> GetIcon() const;

protected:
	virtual void BeginPlay() override;

private:
	TArray<UBaseSlot*> Slots;	
};
