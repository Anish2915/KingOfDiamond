// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_WaitLobby.generated.h"

/**
 * 
 */
UCLASS()
class KINGOFDIAMONDGAME_API UW_WaitLobby : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
public:
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* VerticalPlayerBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* IP_Address_lobby;

	UPROPERTY(meta = (BindWidget))
	class UButton* StartGameButton;
	
	class APC_WaitLobby* PlayerController;

	UFUNCTION()
	void startButtonFunc();
};
