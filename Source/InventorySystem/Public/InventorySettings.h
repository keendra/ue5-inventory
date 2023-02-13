// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "Engine/DataAsset.h"
#include "InventorySettings.generated.h"

/**
 * UInventorySettings is a data asset class that contains information about the settings for a specific item in the
 * inventory system.
 */
UCLASS()
class INVENTORYSYSTEM_API UInventorySettings : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * The name of the item.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Settings")
	FString Name;

	/**
	 * The icon that represents the item in the inventory UI.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Settings")
	TSoftObjectPtr<UTexture2D> Icon;

	/**
	 * The parent type of the item, used for categorization.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Settings")
	TSubclassOf<UBaseItem> ParentType;

	/**
	 * Whether or not the item should be displayed in the inventory UI.
	 * For example when this should be displayed separately.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Settings")
	bool Show = true;

	/**
	 * Overrides the implementation of UPrimaryDataAsset to return a unique identifier for the item.
	 */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("InventorySettings", GetFName());
	}
};
