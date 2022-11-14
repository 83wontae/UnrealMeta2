// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingGameHUD.h"
#include "Blueprint/UserWidget.h"

void AShootingGameHUD::BeginPlay()
{
	Super::BeginPlay();

	check(HudWidgetClass);

	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();
}
