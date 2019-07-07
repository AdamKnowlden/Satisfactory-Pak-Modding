#pragma once

#include "Components/VerticalBox.h"
#include "FGMultiplayerVerticalBox.generated.h"

UCLASS()
class UFGMultiplayerVerticalBox : public UVerticalBox
{
	GENERATED_BODY()

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	UFUNCTION(BlueprintCallable)
	void Sort();

	virtual TSharedRef<SWidget> RebuildWidget() override;
};
