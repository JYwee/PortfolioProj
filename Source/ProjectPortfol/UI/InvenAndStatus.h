// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TileView.h"
#include "InvenAndStatus.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTPORTFOL_API UInvenAndStatus : public UUserWidget
{
	GENERATED_BODY()
	

public:

	// GameMode아니면 HUD 로 수정할것
	//static UInventoryUserWidget* InvenWidget;

	UFUNCTION(BlueprintCallable)
		void AddInvenItem(UObject* data, UUserWidget* widget);

	//UFUNCTION(BlueprintCallable)
	//	void NewWidget(UUserWidget* widget);

	void AddGameItem(const struct FItemDataTable* data);

protected:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTileView* mInvenList = nullptr;
};
