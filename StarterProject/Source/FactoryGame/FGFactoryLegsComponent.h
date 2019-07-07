#pragma once

#include "Components/SceneComponent.h"
#include "FGSaveInterface.h"
#include "FGFactoryLegsComponent.generated.h"

USTRUCT()
struct FFeetOffset
{
	GENERATED_BODY()

	FFeetOffset(){}

	FFeetOffset( const FName& inFeetName ) :
		FeetName( inFeetName ),
		OffsetZ( 0.f ),
		ShouldShow( true ),
		IsValidOffset( true )
	{
	}

	/** The name of the foot's socket. */
	UPROPERTY( SaveGame )
	FName FeetName;

	/** The offset along the Z axis from the parent mesh origo. */
	UPROPERTY( SaveGame )
	float OffsetZ;

	//@todo Not used anymore.
	/** The foot should potentially be invisible. */
	UPROPERTY( SaveGame )
	uint8 ShouldShow : 1;

	/** Does this foot have a valid offset. */
	UPROPERTY( )
	uint8 IsValidOffset : 1;
};

UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class UFGFactoryLegsComponent : public USceneComponent, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;


	UFGFactoryLegsComponent();

	//~ Begin UActorComponent interface
#if WITH_EDITOR
#endif
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	//~ End UActorComponent interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Get all the leg meshes. */
	UFUNCTION( BlueprintCallable, Category = "Legs" )
	TArray< class UStaticMeshComponent* > GetLegMeshComponents() const { return mLegMeshComponents; }
	/** Get all the foot meshes. */
	UFUNCTION( BlueprintCallable, Category = "Legs" )
	TArray< class UStaticMeshComponent* > GetFootMeshComponents() const { return mFootMeshComponents; }

	/** Trace for the feet offsets and return the results. */
	TArray< FFeetOffset > TraceFeetOffsets( const FTransform& actorTransform ) const;

	/** Set/get the feet offsets from external data, must be set prior to BeginPlay. */
	void SetFeetOffsets( const TArray< FFeetOffset >& offsets );
	TArray< FFeetOffset > GetCachedFeetOffsets() const { return mCachedFeetOffset; }

	float GetMaxLegLength() const;

private:
	FFeetOffset TraceFootOffset( FName socket, const FTransform& actorTransform ) const;

	class UStaticMesh* GetLegMesh() const;
	class UStaticMesh* GetFootMesh() const;

	void CreateLegs();
	void RemoveLegs();

	void CreateFoot( const FFeetOffset& offset );

protected:
	/** Socket names on the parent mesh */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	TArray< FName > mLegSocketNames;

	/** The mesh to be used as legs on factories */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	class UStaticMesh* mLegMeshOverride;

	/** The mesh to be used as foots on factories */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	class UStaticMesh* mFootMeshOverride;

	/** The maximum length the legs can be. */
	UPROPERTY( EditDefaultsOnly, Category = "Legs" )
	float mMaxLegLengthOverride;

private:
	/** The created leg components for this building */
	UPROPERTY( transient )
	TArray< UStaticMeshComponent* > mLegMeshComponents;

	/** The created foot components for this building */
	UPROPERTY( transient )
	TArray< UStaticMeshComponent* > mFootMeshComponents;

	/** Stored so that we know the offset of the feets */
	UPROPERTY( SaveGame, Replicated )
	TArray< FFeetOffset > mCachedFeetOffset;
};
