// Fill out your copyright notice in the Description page of Project Settings.


#include "EYS/Interactable Actor/EYS_NotebookWidget.h"

void UEYS_NotebookWidget::NativeConstruct()
{
    Super::NativeConstruct();

  
    CurentRow = 0;

   
    
   
    

    

}

void UEYS_NotebookWidget::SetCleaningBox(int32 finished, int32 total)
{
    int32 RowValue = 0;
    if (CurentRow == 0)
        RowValue = CurentRow;
    else
        RowValue = CurentRow + 1;


    if (GridPanel && CleaningBox)
    {
        GridPanel->AddChildToGrid(CleaningBox, RowValue, 0);
        CleaningBox->SetVisibility(ESlateVisibility::Visible);
    }

    FString TextToShow = "Cleaning: " + FString::FromInt(finished) + "/" + FString::FromInt(total);
    CleaningText->SetText(FText::FromString(TextToShow));
    CurentRow++;
}

void UEYS_NotebookWidget::SetFixingBox(int32 finished, int32 total)
{
    int32 RowValue = 0;
    if (CurentRow == 0)
        RowValue = CurentRow;
    else
        RowValue = CurentRow + 1;

    if (GridPanel && FixingBox)
    {
        
        GridPanel->AddChildToGrid(FixingBox, RowValue,0);
        FixingBox->SetVisibility(ESlateVisibility::Visible);
        
    }
    CurentRow++;

    FString TextToShow = "Fixing: " + FString::FromInt(finished) + "/" + FString::FromInt(total);
    FixingText->SetText(FText::FromString(TextToShow));
}

void UEYS_NotebookWidget::SetFuelingBox(int32 finished, int32 total)
{
    int32 RowValue = 0;
    if (CurentRow == 0)
        RowValue = CurentRow;
    else
        RowValue = CurentRow + 1;

    if (GridPanel && FuelingBox)
    {
        GridPanel->AddChildToGrid(FuelingBox, RowValue, 0);
        FuelingBox->SetVisibility(ESlateVisibility::Visible);
    }
    FString TextToShow = "Fuel: " + FString::FromInt(finished) + "/" + FString::FromInt(total);
    FuelingText->SetText(FText::FromString(TextToShow));
    CurentRow++;
}
