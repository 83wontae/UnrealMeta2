// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponInterface.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class SHOOTINGGAME_API AWeapon : public AActor, public IWeaponInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PressTrigger();

	virtual void PressTrigger_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void NotifyShoot();

	virtual void NotifyShoot_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PressReload();

	virtual void PressReload_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IsCanUse(bool& IsCanUse);

	virtual void IsCanUse_Implementation(bool& IsCanUse) override;

public:
	UFUNCTION(Server, Reliable)
	void ReqShoot(const FVector vStart, const FVector vEnd);

	UFUNCTION()
	void OnRep_Ammo();

	UFUNCTION(BlueprintCallable)
	void UpdateAmmoToHud();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* Audio;

	UPROPERTY(Replicated, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	ACharacter* OwnChar;

	UPROPERTY(Replicated, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	UAnimMontage* AnimMontage_Shoot;

	UPROPERTY(Replicated, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	UAnimMontage* AnimMontage_Reload;

	UPROPERTY(Replicated, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	UParticleSystem* FireEffect;

	UPROPERTY(Replicated, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	USoundBase* SoundBase;

	UPROPERTY(ReplicatedUsing = OnRep_Ammo)
	int Ammo;
};
