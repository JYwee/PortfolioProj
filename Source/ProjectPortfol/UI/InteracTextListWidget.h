// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "InteracTextListWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UInteracTextListWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	//UFUNCTION()
	UFUNCTION(BlueprintCallable)
		void AddInteracTextSlot(UObject* objData, UUserWidget* widgetData);

	UFUNCTION(BlueprintCallable)
		void NewSlotWidget(UUserWidget* widgetData);

protected:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


private:
	UPROPERTY(Category = "IngameUI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UListView* mListView = nullptr;
};
