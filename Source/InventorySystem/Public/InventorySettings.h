// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "Engine/DataAsset.h"
#include "InventorySettings.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInventorySettings : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Settings")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Settings")
	TSoftObjectPtr<UTexture2D> Icon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Settings")
	TSubclassOf<UBaseItem> ParentType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Settings")
	bool Show = true;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("InventorySettings", GetFName());
	}
};
