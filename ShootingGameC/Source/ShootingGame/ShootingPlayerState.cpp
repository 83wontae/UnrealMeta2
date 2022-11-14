// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingPlayerState.h"
#include "Net/UnrealNetwork.h"

void AShootingPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShootingPlayerState, CurHp);
}

void AShootingPlayerState::OnRep_CurHp()
{
}
