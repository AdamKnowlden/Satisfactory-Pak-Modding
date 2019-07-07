// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGInventoryComponent.h"
#include "FGInventoryComponentTrash.generated.h"

UCLASS()
class FACTORYGAME_API UFGInventoryComponentTrash : public UFGInventoryComponent
{
	GENERATED_BODY()

public:
	// Begin UFGInventoryComponent interface
	virtual void OnItemsAdded( int32 idx, int32 num ) override;
	// End UFGInventoryComponent interface
};
