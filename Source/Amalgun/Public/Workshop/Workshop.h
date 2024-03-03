// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Workshop.generated.h"

class UBoxComponent;
class UChildActorComponent;

UCLASS()
class AMALGUN_API AWorkshop : public AActor
{
	GENERATED_BODY()
	
public:	
	AWorkshop();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* RootBoxComponent;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* ChildActorComponent;

};
