// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OutlineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/StaticMesh.h"

// Sets default values for this component's properties
UOutlineComponent::UOutlineComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UOutlineComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

