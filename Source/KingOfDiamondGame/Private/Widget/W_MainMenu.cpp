// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/W_MainMenu.h"
#include "Components/EditableTextBox.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UW_MainMenu::NativeConstruct()
{
    Super::NativeConstruct();
    PlayerName = GetComputerNameFunc();
    NameBlock->SetText(FText::FromString(FString::Printf(TEXT("%s"), *PlayerName)));
    ChangingName->OnTextCommitted.AddDynamic(this, &UW_MainMenu::OnChangingNameTextCommitted);
    InputNoOfPlayer->OnTextCommitted.AddDynamic(this,&UW_MainMenu::UpdateNoOfPlayers);
    SessionButton->OnClicked.AddDynamic(this, &UW_MainMenu::CreateSession);
}




/// Editable Text changed
void UW_MainMenu::OnChangingNameTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
    UpdateName(Text);
}



void UW_MainMenu::CreateSession()
{
    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
    if (OnlineSub) {
        IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
        if (SessionInterface.IsValid()) {
            FOnlineSessionSettings SessionSettings;

            SessionInterface->DestroySession("MySessionName");

            SessionSettings.NumPublicConnections = NoOfPlayer; 
            SessionSettings.bIsLANMatch = true; 
            SessionSettings.bShouldAdvertise = true; 
            SessionSettings.bUsesPresence = true;
            SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UW_MainMenu::OnCreateSessionComplete);
            SessionInterface->CreateSession(0, TEXT("MySessionName"), SessionSettings);
        }
    }
}

void UW_MainMenu::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
    if (bWasSuccessful){
        UWorld* world = GetWorld();
        world->ServerTravel("/Game/Maps/M_WaitLobby?listen");
    }
    else{
        UE_LOG(LogTemp, Warning, TEXT("Not Connected"));
    }
}


/// Editable Text Changed NoOfPlayer
void UW_MainMenu::UpdateNoOfPlayers(const FText& NewText , ETextCommit::Type CommitMethod)
{
    if (NewText.ToString().IsNumeric()){
        NoOfPlayer = FCString::Atoi(*NewText.ToString());
        if (NoOfPlayer <= 0) {
            NoOfPlayer = 5;
        }
    }
    else{
        NoOfPlayer = 5;
    }
}




/// simple update Name
void UW_MainMenu::UpdateName(const FText& NewText)
{
    PlayerName = NewText.ToString();
    if (PlayerName.IsEmpty()) {
        PlayerName = FString("Unknown");
    }
    UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerName);
    NameBlock->SetText(FText::FromString(FString::Printf(TEXT("%s"), *PlayerName)));
}




//// Computer Name
FString UW_MainMenu::GetComputerNameFunc()
{
    const TCHAR* temp = FGenericPlatformProcess::ComputerName();
    if (FString(temp).IsEmpty()) {
        return FString("Random");
    }
    else {
        return temp;
    }
    
}

