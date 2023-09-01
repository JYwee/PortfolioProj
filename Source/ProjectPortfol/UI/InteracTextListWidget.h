// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
//#include "Blueprint/IUserObjectListEntry.h"
#include "InteracTextListWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UInteracTextListWidget : public UUserWidget /*, public IUserObjectListEntry*/
{
	GENERATED_BODY()
	

public:
	//UFUNCTION()
	UFUNCTION(BlueprintCallable)
		void AddInteracTextSlot(UObject* objData, UUserWidget* widgetData);

	UFUNCTION(BlueprintCallable)
		void NewSlotWidget(UUserWidget* widgetData);

	//virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UListView* GetInteractListView() const { return mListView; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UObject* GetNowFocusSlotObj() const { return mFocusNowObjData; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetNowFocusSlotObj(UObject* nextFocusObj) { mFocusNowObjData = nextFocusObj; }


	UFUNCTION(BlueprintCallable)
		UObject* GetUpFocusSlotObj();

	UFUNCTION(BlueprintCallable)
		UObject* GetDownFocusSlotObj();

		UFUNCTION(BlueprintCallable)
	void Function(UUserWidget* _Data);

protected:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	

private:
	UPROPERTY(Category = "IngameUI", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UListView* mListView = nullptr;

	UPROPERTY(Category = "AMainCharacter", BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UObject* mFocusNowObjData = nullptr;
};
