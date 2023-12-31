﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "../Data/ObjDataTable.h"
#include "InteracObjData.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "InteracTextSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UInteracTextSlot : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:

	//바인드 백그라운드 애로우 둘다 이거 하나로 해놓음.
	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
		ESlateVisibility mArrowFocusVisibility = ESlateVisibility::Hidden;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite)
		ESlateVisibility mTextSlotVisibility = ESlateVisibility::Hidden;
	
	UPROPERTY(Category = "Count", EditAnywhere, BlueprintReadWrite)
		UImage* mArrowImg = nullptr;

	UPROPERTY(Category = "Count", EditAnywhere, BlueprintReadWrite)
		UImage* mArrowBGImg = nullptr;

	UPROPERTY(Category = "Count", EditAnywhere, BlueprintReadWrite)
		UTextBlock* mTextBlock = nullptr;


	void SetItemData(const FObjDataTable* objData);

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	

protected:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	

private:
	const UInteracObjData* mObjData = nullptr;
	//const FObjDataTable* mObjData = nullptr;
};
