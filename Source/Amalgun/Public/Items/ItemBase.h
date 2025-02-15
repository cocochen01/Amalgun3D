// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataStructs.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class AMALGUN_API UItemBase : public UObject
{
	GENERATED_BODY()

public:
	/////// Variables ///////
	//UPROPERTY()
	//UInventoryComponent* OwningInventory;
	UPROPERTY(VisibleAnywhere, Category = "Item Data", meta = (UIMin = 1, UIMax=100))
	int32 Quantity;
	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	FName ID;
	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	EItemType ItemType;
	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	EItemQuality ItemQuality;
	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	FItemStats ItemStats;
	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	FItemTextData TextData;
	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	FItemNumericData NumericData;
	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	FItemAssetData AssetData;

	/////// Functions ///////
	UItemBase();

	UItemBase* CreateItemCopy() const;

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemStackWeight() const { return Quantity * NumericData.Weight; };
	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemSingleWeight() const { return NumericData.Weight; };
	UFUNCTION(Category = "Item")
	FORCEINLINE bool IsFullItemStack() const { return Quantity >= NumericData.MaxStackSize; };

	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	//virtual void Use(ACharacterBase* Character);

protected:
	bool operator==(const FName& OtherID) const
	{
		return this->ID == OtherID;
	}

};
