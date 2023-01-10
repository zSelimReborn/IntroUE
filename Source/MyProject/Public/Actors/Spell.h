// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spell.generated.h"

UENUM()
enum class ESpellType
{
	Blast		UMETA(DisplayName="Blast"),
	Storm		UMETA(DisplayName="Storm")
};

UCLASS()
class MYPROJECT_API ASpell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void DealDamage(AActor*);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE float GetManaCost() const { return ManaCost; }
	ESpellType GetSpellType() const { return SpellType; }
	
	// Generic interface for spells
	virtual void Cast(const FVector&);
	virtual void CastAtLocation(const FVector&);

protected:
	UPROPERTY(EditAnywhere, meta=(ClampMin=0.f), Category=Spell)
	float Damage = 5.f;

	UPROPERTY(EditAnywhere, meta=(ClampMin=0.f), Category=Spell)
	float ManaCost = 10.f;
	
	UPROPERTY(EditAnywhere, Category=Spell)
	TObjectPtr<UParticleSystem> HitParticle;

	UPROPERTY(EditAnywhere, Category=Spell)
	ESpellType SpellType = ESpellType::Blast;

	UPROPERTY(EditAnywhere, Category=Spell)
	TSubclassOf<UDamageType> DamageType;
};
