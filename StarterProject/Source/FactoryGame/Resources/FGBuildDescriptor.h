// Copyright 2017 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Resources/FGItemDescriptor.h"
#include "FGBuildDescriptor.generated.h"

/**
*
*/
UCLASS( Abstract )
class FACTORYGAME_API UFGBuildDescriptor : public UFGItemDescriptor
{
	GENERATED_BODY()

public:

#if WITH_EDITOR
	/** When this is changed in the editor, propagate the changes to the preview window */
	virtual void PostEditChangeProperty( struct FPropertyChangedEvent& propertyChangedEvent ) override;
#endif
	
	/** Get the category for this building descriptor. */
	UFUNCTION( BlueprintPure, Category = "Building" )
	static TSubclassOf< class UFGBuildCategory > GetBuildCategory( TSubclassOf< UFGBuildDescriptor > inClass );

	/** Get the category for this building descriptor. */
	UFUNCTION( BlueprintCallable, Category = "Building" )
	static void GetSubCategories( TSubclassOf< UFGBuildDescriptor > inClass, UPARAM( ref ) TArray< TSubclassOf< class UFGBuildSubCategory > >& out_subCategories );

	/** The order we want stuff in the build menu, lower is earlier */
	UFUNCTION( BlueprintPure, Category = "Building" )
	static float GetBuildMenuPriority( TSubclassOf< UFGBuildDescriptor > inClass );

protected:
	/** The category in the build menu for this building */
	UPROPERTY( EditDefaultsOnly, Category = "Building" )
	TSubclassOf< UFGBuildCategory > mBuildCategory;

	/** The sub categories in the build menu for this building */
	UPROPERTY( EditDefaultsOnly, Category = "Building|SubCategories" )
	TArray< TSubclassOf< UFGBuildSubCategory > > mSubCategories;

	/** The order in the Build Menu is decided by this value. Lower values means earlier in menu. Negative values are allowed. [-N..0..N]*/
	UPROPERTY( EditDefaultsOnly, Category = "Building" )
	float mBuildMenuPriority;

};
