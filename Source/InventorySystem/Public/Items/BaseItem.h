// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseItem.generated.h"

/**
 * Base class for all items in the inventory system.
 * This class extends the UPrimaryDataAsset, which is a type of Unreal Engine's data asset
 * that can be referenced by a primary asset ID and can be used as the base class for creating
 * assets that can be managed by the Content Browser and the Asset Registry.
 */
UCLASS(Blueprintable, BlueprintType)
class INVENTORYSYSTEM_API UBaseItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * Override of the GetPrimaryAssetId function from UPrimaryDataAsset
	 *
	 * @return The primary asset ID for this item.
	 */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Item", GetFName());
	}

	/**
	 * The title of the item. This is used to display a brief description of the item.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory Item")
	FString Title;

	/**
	 * The description of the item. This is used to display more detailed information about the item.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory Item")
	FString Description;

	/**
	 * The preview image of the item. This is used to display a visual representation of the item.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory Item")
	TSoftObjectPtr<UTexture2D> Preview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Renderable")
	TSubclassOf<AActor> TemplateActor;

	/**
	 * The weight of the item. This is used to determine the overall weight of items in the inventory.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory Item")
	float Weight;

	/**
	 * The maximum stack size of the item. This is used to determine the maximum number of items that can be stacked in a single slot in the inventory.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory Item")
	int MaxStackSize;

	/**
	 * The base price of the item. This is used to determine the cost of the item in the game world.
	 * The key is a UBaseItem, which represents the item that is used as currency.
	 * The value is the amount of the currency item that is required to purchase a single unit of this item.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory Item")
	TMap<UBaseItem*, int> BasePrice;
};
