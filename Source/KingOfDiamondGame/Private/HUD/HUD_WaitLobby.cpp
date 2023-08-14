// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HUD_WaitLobby.h"
#include "Widget/W_WaitLobby.h"
#include "PlayerController/PC_WaitLobby.h"
#include "Components/VerticalBox.h"
#include "Misc/W_Lobby_Vertical.h"
#include "Components/TextBlock.h"

void AHUD_WaitLobby::BeginPlay()
{
	Super::BeginPlay();
	AddWidget();
}

void AHUD_WaitLobby::AddWidget()
{
	PC_WaitLobbyRef = Cast<APC_WaitLobby>(GetOwningPlayerController());
	if (PC_WaitLobbyRef && SelectedLobbyWid ) {
		W_LobbyRef = CreateWidget<UW_WaitLobby>(PC_WaitLobbyRef, SelectedLobbyWid);
		W_LobbyRef->AddToViewport();
	}
}

void AHUD_WaitLobby::AddPlayer(const FText& NameText)
{
	if (W_LobbyRef && PC_WaitLobbyRef) {
		UW_Lobby_Vertical* verticalRef = CreateWidget<UW_Lobby_Vertical>(PC_WaitLobbyRef, SelectedLobbyWidVertical);
		verticalRef->SNo->SetText(FText::FromString(FString::Printf(TEXT("%d)-"),sNO)));
		verticalRef->Name->SetText(NameText);
		W_LobbyRef->VerticalPlayerBox->AddChild(verticalRef);
		sNO++;
	}
}
