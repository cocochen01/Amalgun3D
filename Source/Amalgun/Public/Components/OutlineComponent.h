// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OutlineComponent.generated.h"

class UMaterialInterface;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AMALGUN_API UOutlineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UOutlineComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Outline")
	UMaterialInterface* OutlineMaterial;

protected:
	virtual void BeginPlay() override;
};
