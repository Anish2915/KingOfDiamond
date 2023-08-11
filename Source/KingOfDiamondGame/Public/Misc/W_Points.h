// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Points.generated.h"

/**
 * 
 */
UCLASS()
class KINGOFDIAMONDGAME_API UW_Points : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PoitsText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameText;
};
