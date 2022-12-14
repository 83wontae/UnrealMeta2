// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShootingPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FDele_Multi_UpdateHp_TwoParams, float, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FDele_Multi_UpdateMag_OneParam, int);
/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API AShootingPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AShootingPlayerState();

protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurHp)
	float CurHp;

	UPROPERTY(ReplicatedUsing = OnRep_MaxHp)
	float MaxHp;

	UPROPERTY(ReplicatedUsing = OnRep_Mag)
	int Mag;

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetCurHp() const { return CurHp; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetMaxHp() const { return MaxHp; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetMag() const { return Mag; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsCanUseMag() const { return ( Mag > 0 ) ? true : false; }

public:
	UFUNCTION()
	void OnRep_CurHp();

	UFUNCTION()
	void OnRep_MaxHp();

	UFUNCTION()
	void OnRep_Mag();

	UFUNCTION(BlueprintCallable)
	void AddDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void AddHeal(float Heal);

	UFUNCTION(BlueprintCallable)
	void AddMag();

	UFUNCTION(BlueprintCallable)
	bool UseMag();

	FDele_Multi_UpdateHp_TwoParams Fuc_Dele_UpdateHp_TwoParams;
	FDele_Multi_UpdateMag_OneParam Fuc_Dele_UpdateMag_OneParam;
};
