// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameHUD.h"
#include "Blueprint/UserWidget.h"

void AShootingGameHUD::OnUpdateMyHp_Implementation(float CurrentHp)
{
}

void AShootingGameHUD::BeginPlay()
{
	Super::BeginPlay();

	check(HudWidgetClass);

	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();
}
