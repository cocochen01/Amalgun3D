#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "ItemDataStructs.generated.h"

UENUM()
enum class EItemQuality : uint8
{
	Shoddy UMETA(DisplayName = "Shoddy"),
	Common UMETA(DisplayName = "Common"),
	Quality UMETA(DisplayName = "Quality"),
	Masterwork UMETA(DisplayName = "Masterwork"),
	Grandmaster UMETA(DisplayName = "Grandmaster")
};

UENUM()
enum class EItemType : uint8
{
	Gun UMETA(DisplayName = "Gun"),
	Melee UMETA(DisplayName = "Melee"),
	Defensive UMETA(DisplayName = "Defensive"),
	Artifact UMETA(DisplayName = "Artifact"),
	Consumable UMETA(DisplayName = "Consumable")
};

USTRUCT()
struct FItemStats
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	float DamageValue;
	UPROPERTY(EditAnywhere)
	float RangeValue;
	UPROPERTY(EditAnywhere)
	float DefenseValue;
	UPROPERTY(EditAnywhere)
	float AttackSpeed;
};

USTRUCT()
struct FItemTextData
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	FText Name;
	UPROPERTY(EditAnywhere)
	FText Description;
	UPROPERTY(EditAnywhere)
	FText InteractionText;
	UPROPERTY(EditAnywhere)
	FText UsageText;
};

USTRUCT()
struct FItemNumericData
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	float Weight;
	UPROPERTY(EditAnywhere)
	int32 MaxStackSize;
	UPROPERTY(EditAnywhere)
	bool bIsStackable;
};

USTRUCT()
struct FItemAssetData
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;
	//Sound effect
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName ID;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemType ItemType;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	EItemQuality ItemQuality;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemStats ItemStats;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemTextData TextData;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData NumericData;
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData AssetData;
};
