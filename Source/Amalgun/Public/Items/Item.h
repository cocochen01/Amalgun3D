// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "Item.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UWidgetComponent;
class ACharacterBase;

UENUM(BlueprintType)
enum class EItemState : uint8
{
	EIS_Initial UMETA(DisplayName = "Initial State"),
	EIS_Equipped UMETA(DisplayName = "Equipped"),
	EIS_Dropped UMETA(DisplayName = "Dropped"),

	EIS_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class AMALGUN_API AItem : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:
	/////// Variables ///////
	
	/////// Functions ///////
	AItem();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void ShowWidget();
	UFUNCTION()
	void HideWidget();

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteract() override;
	virtual void EndInteract() override;
	virtual void Interact(ACharacterBase*) override;

protected:
	/////// Variables ///////
	UPROPERTY(EditAnywhere, Category = "Item Properties")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, Category = "Item Properties")
	USphereComponent* AreaSphere;

	UPROPERTY(EditAnywhere, Category = "Item Properties")
	EItemState ItemState;

	UPROPERTY(EditAnywhere, Category = "Item Properties")
	UWidgetComponent* PickupWidget;

	/////// Functions ///////
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	/////// Variables ///////
	/////// Functions ///////
};
