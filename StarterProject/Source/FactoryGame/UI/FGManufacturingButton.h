// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGManufacturingButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FManufacturePressed, float, produceMultiplier );

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGManufacturingButton : public UUserWidget
{
	GENERATED_BODY()
public:
	/** Sets our internal button that will be used for focus handling */
	UFUNCTION( BlueprintCallable, Category = "Manufacturing Button" )
	void SetButton( class UButton* inButton );
protected: 
	/** Internal button was pressed */
	UFUNCTION()
	void OnPressedButton();

	/** Internal button was released, added BlueprintCallable to be able to simulate button release */
	UFUNCTION( BlueprintCallable, Category = "Manufacturing Button" )
	void OnReleasedButton();

	virtual void NativeTick( const FGeometry& MyGeometry, float InDeltaTime );
public:
	/** Called when a valid press on manufacture happens */
	UPROPERTY( BlueprintAssignable, Category = "Manufacturing Button" )
	FManufacturePressed OnManufacturePressed;
protected:
	/** Minimum time between button presses to register a manufacture event */
	UPROPERTY( EditDefaultsOnly, Category = "Manufacturing Button" )
	float mMinTimeBetweenPress;

	/** Saving when we last pressed button */
	float mLastPressTime;

	/** Is the button being held? */
	bool mIsHolding;

	/** How long to hold for a manufacture to be called */
	UPROPERTY( EditDefaultsOnly, Category = "Manufacturing Button" )
	float mHoldTimeMax;

	/** produce speed when holding the button */
	UPROPERTY( EditDefaultsOnly, Category = "Manufacturing Button" )
	float mHoldProduceSpeed;

	/** How long has the button been held? */
	float mHoldTime;
private:
	/** Reference to the UButton we have internally */
	class UButton* mInternalButton;
	
};
