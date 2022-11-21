// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Net/UnrealNetwork.h"
#include "Components/AudioComponent.h"
#include "ShootingGameHUD.h"
#include "ShootingGameInstance.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;

	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	Audio->SetupAttachment(RootComponent);

	bReplicates = true;
	SetReplicateMovement(true);

	Ammo = 30;
}

void AWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, OwnChar);
	DOREPLIFETIME(AWeapon, FireEffect);
	DOREPLIFETIME(AWeapon, RowName);
	DOREPLIFETIME(AWeapon, Ammo);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	WeaponData = Cast<UShootingGameInstance>(GetGameInstance())->GetWeaponRowData(RowName);
	if (WeaponData)
	{
		Mesh->SetStaticMesh(WeaponData->StaticMesh);
		Audio->SetSound(WeaponData->SoundBase);
		Mesh->SetCollisionProfileName("Weapon");
		Mesh->SetSimulatePhysics(true);
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::PressTrigger_Implementation()
{
	OwnChar->PlayAnimMontage(WeaponData->ShootMontage);
}

void AWeapon::NotifyShoot_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireEffect, Mesh->GetSocketLocation("Muzzle"), Mesh->GetSocketRotation("Muzzle"), FVector(0.3f, 0.3f, 0.3f));

	Audio->Play();

	APlayerController* shooter = GetWorld()->GetFirstPlayerController();
	if (shooter == OwnChar->GetController())
	{
		FVector forward = shooter->PlayerCameraManager->GetActorForwardVector();

		FVector start = (forward * 350) + shooter->PlayerCameraManager->GetCameraLocation();
		FVector end = (forward * 5000) + shooter->PlayerCameraManager->GetCameraLocation();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Client - ReqShoot")));
		ReqShoot(start, end);
	}
}

void AWeapon::PressReload_Implementation()
{
	OwnChar->PlayAnimMontage(WeaponData->ReloadMontage);
}

void AWeapon::IsCanUse_Implementation(bool& IsCanUse)
{
	if (Ammo <= 0)
	{
		IsCanUse = false;
		return;
	}

	Ammo = Ammo - 1;
	IsCanUse = true;
	OnRep_Ammo();
}

void AWeapon::OnRep_Ammo()
{
	UpdateAmmoToHud();
}

void AWeapon::UpdateAmmoToHud()
{
	//UI 출력 연결
	APlayerController* firstPlayer = GetWorld()->GetFirstPlayerController();

	if (OwnChar->GetController() == firstPlayer)
	{
		AShootingGameHUD* Hud = Cast<AShootingGameHUD>(firstPlayer->GetHUD());
		if (IsValid(Hud))
		{
			Hud->OnUpdateMyAmmo(Ammo);
		}
	}
}

void AWeapon::ReqShoot_Implementation(const FVector vStart, const FVector vEnd)
{
	FHitResult result;
	bool isHit = GetWorld()->LineTraceSingleByObjectType(result, vStart, vEnd, ECollisionChannel::ECC_Pawn);

	DrawDebugLine(GetWorld(), vStart, vEnd, FColor::Yellow, false, 5.0f);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Server - ReqShoot")));

	if (isHit)
	{
		ACharacter* HitChar = Cast<ACharacter>(result.GetActor());
		if (HitChar)
		{
			UGameplayStatics::ApplyDamage(HitChar, 10, OwnChar->GetController(), this, UDamageType::StaticClass());
		}
	}
}

