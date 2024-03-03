// Fill out your copyright notice in the Description page of Project Settings.


#include "Workshop/Workshop.h"
//Components
#include "Components/BoxComponent.h"
#include "Components/ChildActorComponent.h"
//Other Classes
#include "Camera/CameraActor.h"
#include "Character/CharacterBase.h"

// Sets default values
AWorkshop::AWorkshop()
{
	PrimaryActorTick.bCanEverTick = false;

	RootBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBoxComponent"));
	RootComponent = RootBoxComponent;
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(GetRootComponent());
	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("CameraActorComponent"));
	ChildActorComponent->SetupAttachment(CollisionComponent);
	static ConstructorHelpers::FClassFinder<AActor> ChildActorClassFinder(TEXT("Engine.CameraActor"));
	if (ChildActorClassFinder.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Camera Actor Found"));
		ChildActorComponent->SetChildActorClass(ChildActorClassFinder.Class);
	}
}

// Called when the game starts or when spawned
void AWorkshop::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AWorkshop::OnBeginOverlap);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AWorkshop::OnEndOverlap);
}

void AWorkshop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorkshop::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacterBase* Character = Cast<ACharacterBase>(OtherActor);
	if (!Character)
		return;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Begin Overlap"));
	Character->SetCameraView(ChildActorComponent->GetChildActor());
}

void AWorkshop::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacterBase* Character = Cast<ACharacterBase>(OtherActor);
	if (!Character)
		return;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("End Overlap"));
	Character->SetCameraView(nullptr);
}

