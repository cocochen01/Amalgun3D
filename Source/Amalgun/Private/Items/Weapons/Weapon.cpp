// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"

AWeapon::AWeapon()
{
	UArrowComponent* NewArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow1"));
	NewArrow->SetupAttachment(ItemMesh);
	ArrowList.Add(NewArrow);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	InitializeAttachments();
}

void AWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AWeapon::InitializeAttachments()
{
}
