// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_ButtonCPP.generated.h"

/**
 * 
 */
UCLASS()
class KINGOFDIAMONDGAME_API UW_ButtonCPP : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text;
	int value;

	UFUNCTION()
	void OnClick();
};
