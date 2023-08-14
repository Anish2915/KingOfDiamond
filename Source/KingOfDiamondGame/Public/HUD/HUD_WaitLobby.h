// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_WaitLobby.generated.h"

/**
 * 
 */
class APC_WaitLobby;
class UW_WaitLobby;
class UW_Lobby_Vertical;
UCLASS()
class KINGOFDIAMONDGAME_API AHUD_WaitLobby : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	UW_WaitLobby* W_LobbyRef;

	APC_WaitLobby* PC_WaitLobbyRef;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UW_WaitLobby> SelectedLobbyWid;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UW_Lobby_Vertical> SelectedLobbyWidVertical;

	void AddWidget();
	int sNO = 1;

	void AddPlayer(const FText& NameText);
};
