// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "UObject/NoExportTypes.h"
#include "FGSaveInterface.h"
#include "FGRailroadTimeTable.generated.h"

/**
 * A stop entry in the time table.
 */
USTRUCT( BlueprintType )
struct FTimeTableStop
{
	GENERATED_BODY()
public:
	FTimeTableStop();

public:
	/** Where to stop. */
	UPROPERTY( SaveGame, BlueprintReadWrite )
	class AFGBuildableRailroadStation* Stop;

	/** Time to stay. */
	UPROPERTY( SaveGame, BlueprintReadWrite )
	float Duration;
};

/**
 * Object containing a trains time table and where it is right now.
 */
UCLASS( BlueprintType )
class FACTORYGAME_API UFGRailroadTimeTable : public UObject, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	/** Ctor */
	UFGRailroadTimeTable();

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Add a stop to the time table. */
	UFUNCTION( BlueprintCallable, Category = "TimeTable" )
	void AddStop( int32 index, const FTimeTableStop& stop );

	/** Remove a stop from the time table. */
	UFUNCTION( BlueprintCallable, Category = "TimeTable" )
	void RemoveStop( int32 index );

	/** Get the number of stops. */
	UFUNCTION( BlueprintPure, Category = "TimeTable" )
	FORCEINLINE int32 GetNumStops() const { return mStops.Num(); }

	/** Get all stops in the time table. */
	UFUNCTION( BlueprintCallable, Category = "TimeTable" )
	void GetStops( TArray< FTimeTableStop >& out_stops ) const;

	/**
	 * Is the index a valid stop.
	 * Checks if the index is valid and the 'Stop' actor is valid. 
	 */
	UFUNCTION( BlueprintPure, Category = "TimeTable" )
	bool IsValidStop( int32 index ) const;

	/**
	 * Get the given stop.
	 * @return The stop at index, valid or invalid. If the index is invalid it returns an empty stop.
	 */
	UFUNCTION( BlueprintCallable, Category = "TimeTable" )
	FTimeTableStop GetStop( int32 index ) const;

	/** @return Current stop the train is at or heading to. */
	UFUNCTION( BlueprintPure, Category = "TimeTable" )
	FORCEINLINE int32 GetCurrentStop() const { return mCurrentStop; }

	/** @param index Set the stop the train is heading to. */
	UFUNCTION( BlueprintCallable, Category = "TimeTable" )
	void SetCurrentStop( int32 index ) { mCurrentStop = index; }

	/**
	 * @param index Which stop to modify, this function does nothing if invalid.
	 * @param Duration How long the train will stay at the station (seconds)
	 */
	UFUNCTION( BlueprintCallable, Category = "TimeTable" )
	void SetStopDuration( int32 index, float duration );

private:
	/** Array of destinations this train will visit. */
	UPROPERTY( SaveGame )
	TArray< FTimeTableStop > mStops;

	/** Current stop the train is at or heading to. */
	UPROPERTY( SaveGame )
	int32 mCurrentStop;
};
