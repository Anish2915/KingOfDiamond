// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Arena.generated.h"

class UButton;
UCLASS()
class KINGOFDIAMONDGAME_API UW_Arena : public UUserWidget
{
	GENERATED_BODY()

public:

protected:
    virtual void NativeConstruct() override;
    
public:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ArenaTimer;


    UPROPERTY(meta = (BindWidget))
    class UHorizontalBox* MyHorizontalBox;
};
