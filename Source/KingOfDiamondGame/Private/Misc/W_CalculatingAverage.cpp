// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/W_CalculatingAverage.h"
#include "Components/TextBlock.h"


void UW_CalculatingAverage::Calc2()
{
	UE_LOG(LogTemp, Warning, TEXT("%d"), choosenArr.Num());
	if (choosenArr.Num() >= 1) choosen1->SetText(FText::FromString(FString::Printf(TEXT("%f"),choosenArr[0])));
	if (choosenArr.Num() >= 2) choosen2->SetText(FText::FromString(FString::Printf(TEXT("%f"), choosenArr[1])));
	if (choosenArr.Num() >= 3) choosen3->SetText(FText::FromString(FString::Printf(TEXT("%f"), choosenArr[2])));
	if (choosenArr.Num() >= 4) choosen4->SetText(FText::FromString(FString::Printf(TEXT("%f"), choosenArr[3])));
	if (choosenArr.Num() >= 5) choosen5->SetText(FText::FromString(FString::Printf(TEXT("%f"), choosenArr[4])));
	average->SetText(FText::FromString(FString::Printf(TEXT("%f"), averag)));
	final->SetText(FText::FromString(FString::Printf(TEXT("%f"), averag*0.8)));
	Calc();
}

void UW_CalculatingAverage::UpdatePoints()
{
	
	if( PointsArr.Num() >= 1)point1->SetVisibility(ESlateVisibility::Visible);
	if (PointsArr.Num() >= 2)point2->SetVisibility(ESlateVisibility::Visible);
	if (PointsArr.Num() >= 3)point3->SetVisibility(ESlateVisibility::Visible);
	if (PointsArr.Num() >= 4)point4->SetVisibility(ESlateVisibility::Visible);
	if (PointsArr.Num() >= 5)point5->SetVisibility(ESlateVisibility::Visible);
}

void UW_CalculatingAverage::UpdatePoint2()
{
	if (PointsArr.Num() >= 1)point1->SetText(FText::FromString(FString::Printf(TEXT("%d"), PointsArr[0])));
	if (PointsArr.Num() >= 2)point2->SetText(FText::FromString(FString::Printf(TEXT("%d"), PointsArr[1])));
	if (PointsArr.Num() >= 3)point3->SetText(FText::FromString(FString::Printf(TEXT("%d"), PointsArr[2])));
	if (PointsArr.Num() >= 4)point4->SetText(FText::FromString(FString::Printf(TEXT("%d"), PointsArr[3])));
	if (PointsArr.Num() >= 5)point5->SetText(FText::FromString(FString::Printf(TEXT("%d"), PointsArr[4])));


}

void UW_CalculatingAverage::UpdateWinnerStatus()
{
	TArray<UTextBlock*> teemp;
	teemp.Add(Winner1);
	teemp.Add(Winner2);
	teemp.Add(Winner3);
	teemp.Add(Winner4);
	teemp.Add(Winner5);
	for (int i = 0; i < WinnerStatsWid.Num(); i++) {
		if (WinnerStatsWid[i]) {
			teemp[i]->SetVisibility(ESlateVisibility::Visible);
		}
	}


}

void UW_CalculatingAverage::RemoveWinnerStat()
{
	TArray<UTextBlock*> teemp;
	teemp.Add(Winner1);
	teemp.Add(Winner2);
	teemp.Add(Winner3);
	teemp.Add(Winner4);
	teemp.Add(Winner5);
	for (int i = 0; i < 5; i++) {
		teemp[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UW_CalculatingAverage::CheckDead()
{

}


