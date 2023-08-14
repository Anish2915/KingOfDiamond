// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Lobby_Vertical.generated.h"

/**
 * 
 */
UCLASS()
class KINGOFDIAMONDGAME_API UW_Lobby_Vertical : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SNo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name;
};
