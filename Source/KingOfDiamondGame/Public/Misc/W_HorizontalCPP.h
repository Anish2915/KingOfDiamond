// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_HorizontalCPP.generated.h"

UCLASS()
class KINGOFDIAMONDGAME_API UW_HorizontalCPP : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* MyVerticalBox;

	
};
