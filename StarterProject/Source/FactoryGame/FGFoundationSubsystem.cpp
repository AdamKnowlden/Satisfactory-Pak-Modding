// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGFoundationSubsystem.h"

void AFGFoundationSubsystem::Serialize(FArchive& ar){ Super::Serialize(ar); }
void AFGFoundationSubsystem::DisplayDebug(  UCanvas* canvas, const  FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ){ }
void AFGFoundationSubsystem::PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ){ }
void AFGFoundationSubsystem::PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ){ }
void AFGFoundationSubsystem::PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ){ }
void AFGFoundationSubsystem::PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ){ }
void AFGFoundationSubsystem::GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ){ }
bool AFGFoundationSubsystem::NeedTransform_Implementation(){ return bool(); }
bool AFGFoundationSubsystem::ShouldSave_Implementation() const{ return bool(); }
AFGFoundationSubsystem* AFGFoundationSubsystem::Get( UWorld* world ){ return nullptr; }
void AFGFoundationSubsystem::AddBuildable(  AFGBuildable* buildable, bool isNewBuilding ){ }
void AFGFoundationSubsystem::RemoveBuildable(  AFGBuildable* buildable ){ }
//template< typename T >
//void AFGFoundationSubsystem::GetTypedBuildable( int32 buildingID, TArray< T* >& out_buildables ) const{ }
int32 AFGFoundationSubsystem::GenerateUniqueBuildingID(){ return int32(); }