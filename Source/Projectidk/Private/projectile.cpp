// Fill out your copyright notice in the Description page of Project Settings.


#include "projectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h" 
#include "SAttributeComponent.h"


// Sets default values
Aprojectile::Aprojectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &Aprojectile::OnActorOverlap);
	RootComponent = SphereComp;
	
	ParticleComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ParticleComp"));
	ParticleComp->SetupAttachment(SphereComp);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
}

void Aprojectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if (OtherActor and OtherActor != GetInstigator())
	{
		USAttributeComponent* AttributeComp = OtherActor->FindComponentByClass<USAttributeComponent>();
		
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.0f);
		};
		Destroy();
		
	};
	
}

// Called when the game starts or when spawned
void Aprojectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aprojectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

