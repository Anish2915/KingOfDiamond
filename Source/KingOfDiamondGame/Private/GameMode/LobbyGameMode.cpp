// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "GameInstance/A_GameInstance.h"

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
	UA_GameInstance* GameInstance = Cast<UA_GameInstance>(GetGameInstance());
	if (GameInstance) {
		NoOfPlayer = GameInstance->NoOfPlayer;
	}
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (GameState) {
		int32 NoOfPlayers = GameState.Get()->PlayerArray.Num();

		if (NoOfPlayers == NoOfPlayer) {
			UWorld* World = GetWorld();
			if (World) {
				bUseSeamlessTravel = true;
				World->ServerTravel("/Game/Maps/M_ArenaMap?listen");
			}
		}

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
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();

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
}
