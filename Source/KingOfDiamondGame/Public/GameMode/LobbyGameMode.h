// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class KINGOFDIAMONDGAME_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	class APC_WaitLobby* Server;
	bool b=true;

	void start();

	FTimerHandle Timer;
	APC_WaitLobby* PlayerCont;

	void PostLog();
};
