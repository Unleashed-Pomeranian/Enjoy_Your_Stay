// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_NotebookWidget.h"


void UEYS_NotebookWidget::NativeConstruct()
{
    Super::NativeConstruct();


}
void UEYS_NotebookWidget::RepositionGridMissions()
{
    if (!GridPanel) return;


    GridPanel->ClearChildren();

    int32 ActiveRow = 0;


    if (CleaningBox && CleaningBox->GetVisibility() == ESlateVisibility::Visible)
    {
        GridPanel->AddChildToGrid(CleaningBox, ActiveRow, 0);
        ActiveRow++;
    }


    if (FixingBox && FixingBox->GetVisibility() == ESlateVisibility::Visible)
    {
        GridPanel->AddChildToGrid(FixingBox, ActiveRow, 0);
        ActiveRow++;
    }

   
    if (FuelingBox && FuelingBox->GetVisibility() == ESlateVisibility::Visible)
    {
        GridPanel->AddChildToGrid(FuelingBox, ActiveRow, 0);
        ActiveRow++;
    }
    if (BoilerBox && BoilerBox->GetVisibility() == ESlateVisibility::Visible)
    {
        GridPanel->AddChildToGrid(BoilerBox, ActiveRow, 0);
        ActiveRow++;
    }


    if (SnowPileBox && SnowPileBox->GetVisibility() == ESlateVisibility::Visible)
    {
        GridPanel->AddChildToGrid(SnowPileBox, ActiveRow, 0);
        ActiveRow++;
    }

}

void UEYS_NotebookWidget::SetCleaningBox(int32 finished, int32 total)
{

    if (CleaningBox)
    {
        CleaningBox->SetVisibility(ESlateVisibility::Visible);
    }

    FString TextToShow = FString::Printf(TEXT("-Cleaning Dirts. (%d/%d)"), finished, total);
    if (CleaningText)
    {
        CleaningText->SetText(FText::FromString(TextToShow));
    }

    RepositionGridMissions();
}

void UEYS_NotebookWidget::SetFixingBox(int32 finished, int32 total)
{
    if (FixingBox)
    {
        FixingBox->SetVisibility(ESlateVisibility::Visible);
    }

    FString TextToShow = FString::Printf(TEXT("-Repair Pipes. (%d/%d)"), finished, total);
    if (FixingText)
    {
        FixingText->SetText(FText::FromString(TextToShow));
    }

    RepositionGridMissions();
}

void UEYS_NotebookWidget::SetFuelingBox(int32 finished, int32 total)
{
    if (FuelingBox)
    {
        FuelingBox->SetVisibility(ESlateVisibility::Visible);
    }


    FString TextToShow = FString::Printf(TEXT("-Refuel Generator. (%%%d)"), finished);
    if (FuelingText)
    {
        FuelingText->SetText(FText::FromString(TextToShow));
    }

    RepositionGridMissions();
}
void UEYS_NotebookWidget::SetBoilerBox(int32 finished, int32 total)
{
    if (BoilerBox)
    {
        BoilerBox->SetVisibility(ESlateVisibility::Visible);
    }


    FString TextToShow = FString::Printf(TEXT("-Refuel Boiler. (%%%d)"), finished);
    if (BoilerText)
    {
        BoilerText->SetText(FText::FromString(TextToShow));
    }

    RepositionGridMissions();
}

void UEYS_NotebookWidget::SetSnowPileBox(int32 finished, int32 total)
{
   
    if (SnowPileBox)
    {
        SnowPileBox->SetVisibility(ESlateVisibility::Visible);
    }

    FString TextToShow = FString::Printf(TEXT("-Shovel Snow Piles. (%d/%d)"), finished, total);
    if (SnowPileText)
    {
        SnowPileText->SetText(FText::FromString(TextToShow));
    }

    RepositionGridMissions();
}


void UEYS_NotebookWidget::CleanMissionBox(int32 value)
{
    switch (value)
    {
    case 1:
        if (CleaningBox)
        {
            CleaningBox->SetVisibility(ESlateVisibility::Hidden);
      
        }
        break;

    case 2:
        if (FuelingBox)
        {
            FuelingBox->SetVisibility(ESlateVisibility::Hidden);
         
        }
        break;

    case 3:
        if (FixingBox)
        {
            FixingBox->SetVisibility(ESlateVisibility::Hidden);
          
        }
        break;
    case 4:
        if (BoilerBox)
        {
            BoilerBox->SetVisibility(ESlateVisibility::Hidden);
 
        }
        break;
    case 5:
        if (SnowPileBox)
        {
            SnowPileBox->SetVisibility(ESlateVisibility::Hidden);

        }
        break;

    default:
        break;
    }

    RepositionGridMissions();
}

void UEYS_NotebookWidget::SetStarBarPercent(const float NewValue)
{
    if (ProgressBar_Star)
    {
        ProgressBar_Star->SetPercent(NewValue);
    }
}
