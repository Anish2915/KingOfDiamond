// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/W_WaitLobby.h"
#include "Components/Button.h"
#include "PlayerController/PC_WaitLobby.h"
#include "GameMode/LobbyGameMode.h"
#include "Components/TextBlock.h"

void UW_WaitLobby::NativeConstruct()
{
	StartGameButton->OnClicked.AddDynamic(this, &UW_WaitLobby::startButtonFunc);
	APlayerController* OwningPlayerController = GetOwningPlayer();
	if (OwningPlayerController) {
		PlayerController = Cast<APC_WaitLobby>(OwningPlayerController);
		if (PlayerController->HasAuthority()) {
			StartGameButton->SetVisibility(ESlateVisibility::Visible);
		}
	}
	
}

void UW_WaitLobby::startButtonFunc()
{
	if (PlayerController && PlayerController->HasAuthority()) {
		UE_LOG(LogTemp, Warning, TEXT("button pressed"));
		UWorld* World = GetWorld();
		if (World) {
			UE_LOG(LogTemp, Warning, TEXT("World Find"));
			World->ServerTravel("/Game/Maps/M_ArenaMap?listen");
		}
	}
	


}


