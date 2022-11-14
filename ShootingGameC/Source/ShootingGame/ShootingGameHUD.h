// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShootingGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API AShootingGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> HudWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* HudWidget;

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnUpdateMyHp(float CurrentHp);

	void OnUpdateMyHp_Implementation(float CurrentHp);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
