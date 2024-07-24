// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

class UArrowComponent;
class USphereComponent;
class UCapsuleComponent;
class AItem;


UCLASS()
class AMALGUN_API AWeapon : public AItem
{
	GENERATED_BODY()
	
public:
	/////// Variables ///////

	/////// Functions ///////
	AWeapon();

protected:
	/////// Variables ///////
	UPROPERTY(EditAnywhere, Category = "Weapon Attachments")
	TArray<UArrowComponent*> ArrowList;

	UPROPERTY(EditAnywhere, Category = "Weapon Attachments")
	TArray<AItem*> AttachmentList;

	/////// Functions ///////
	virtual void BeginPlay() override;
	virtual void OnBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnEndOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

private:
	void InitializeAttachments();
};
