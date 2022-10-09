// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Slots/BaseSlot.h"
#include "InventorySettings.h"
#include "Components/ActorComponent.h"
#include "Slots/InventorySlot.h"
#include "Inventory.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventory();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	int BaseSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	float MaxWeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	bool AutoResize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	TSubclassOf<UBaseSlot> SlotClass = UInventorySlot::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	TMap<UBaseItem*, int> InitialItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	UInventorySettings* InventoryConfig;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	TArray<UBaseSlot*> GetInventorySlots();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	TSoftObjectPtr<UTexture2D> GetIcon() const;

protected:
	virtual void BeginPlay() override;

private:
	TArray<UBaseSlot*> Slots;	
};
