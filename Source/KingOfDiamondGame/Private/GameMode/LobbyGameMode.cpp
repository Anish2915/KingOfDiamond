// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "GameInstance/A_GameInstance.h"
#include "PlayerController/PC_WaitLobby.h"
#include "HUD/HUD_WaitLobby.h"
#include "Widget/W_WaitLobby.h"
#include "Components/TextBlock.h"

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
	bUseSeamlessTravel = true;
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	PlayerCont = Cast<APC_WaitLobby>(NewPlayer);

	GetWorldTimerManager().SetTimer(Timer, this, &ALobbyGameMode::PostLog, 3.0f, false);

	
	/*
	if (GameState) {
		int32 NoOfPlayers = GameState.Get()->PlayerArray.Num();

		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, FString::Printf(TEXT("No Of players are %d"), NoOfPlayers));
		}
		APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
		if (PlayerState) {
			FString PlayerName = PlayerState->GetPlayerName();
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Red, FString::Printf(TEXT("%s has joined"), *PlayerName));
			}
		}
	}
	*/
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
	/*
	if (PlayerState) {
		int32 NoOfPlayers = GameState.Get()->PlayerArray.Num();
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, FString::Printf(TEXT("No Of players are %d"), NoOfPlayers - 1));
		}


		FString PlayerName = PlayerState->GetPlayerName();
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Red, FString::Printf(TEXT("%s has Left"), *PlayerName));
		}
	}
	*/
}

void ALobbyGameMode::start()
{
	UWorld* World = GetWorld();
	if (World) {
		bUseSeamlessTravel = true;
		World->ServerTravel("/Game/Maps/M_ArenaMap?listen");
	}
}

void ALobbyGameMode::PostLog()
{
	if (b) {
		Server = PlayerCont;

		if (Server->waitLobby) {
			Server->waitLobby->AddPlayer(FText::FromString(Server->PlayerState->GetPlayerName()));
			b = false;
		}
	}
	else {
		if (Server && Server->waitLobby) {
			Server->waitLobby->AddPlayer(FText::FromString(PlayerCont->PlayerState->GetPlayerName()));
		}
	}
}
