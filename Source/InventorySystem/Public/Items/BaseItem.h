// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseItem.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UBaseItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Item", GetFName());
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	TSoftObjectPtr<UTexture2D> Preview;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	int MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	TMap<UBaseItem*, int> BasePrice;
};
