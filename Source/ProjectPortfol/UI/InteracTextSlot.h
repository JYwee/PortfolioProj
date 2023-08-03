// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "../Data/ObjDataTable.h"
#include "InteracTextSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UInteracTextSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
		ESlateVisibility mTextSlotVisibility = ESlateVisibility::Hidden;
	
	UPROPERTY(Category = "Count", EditAnywhere, BlueprintReadWrite)
		UTextBlock* mTextBlock = nullptr;


	void SetItemData(const FObjDataTable* objData);

protected:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	

private:
	const FObjDataTable* mObjData = nullptr;
};
