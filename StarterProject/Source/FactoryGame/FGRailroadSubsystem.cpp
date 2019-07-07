// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGRailroadSubsystem.h"

FTrain::FTrain(){ }
FTrain::~FTrain(){ }
FTrackGraph::FTrackGraph(){ }
void AFGRailroadSubsystem::GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const{ }
void AFGRailroadSubsystem::PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ){ }
void AFGRailroadSubsystem::PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ){ }
void AFGRailroadSubsystem::PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ){ }
void AFGRailroadSubsystem::PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ){ }
void AFGRailroadSubsystem::GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ){ }
bool AFGRailroadSubsystem::NeedTransform_Implementation(){ return bool(); }
bool AFGRailroadSubsystem::ShouldSave_Implementation() const{ return bool(); }
void AFGRailroadSubsystem::Serialize(FArchive& ar){ Super::Serialize(ar); }
void AFGRailroadSubsystem::BeginPlay(){ }
void AFGRailroadSubsystem::Tick( float dt ){ }
void AFGRailroadSubsystem::DisplayDebug(  UCanvas* canvas, const  FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ){ }
AFGRailroadSubsystem::AFGRailroadSubsystem(){ }
AFGRailroadSubsystem* AFGRailroadSubsystem::Get( UWorld* world ){ return nullptr; }
AFGRailroadSubsystem* AFGRailroadSubsystem::Get( UObject* worldContext ){ return nullptr; }
AFGRailroadVehicle* AFGRailroadSubsystem::SpawnTrain( TSubclassOf<  AFGRailroadVehicle > vehicleClass,
										  const  FRailroadTrackPosition& trackPosition,
										   AFGRailroadVehicle* coupleTo ){ return nullptr; }
void AFGRailroadSubsystem::DestroyTrain(  AFGRailroadVehicle* vehicle ){ }
void AFGRailroadSubsystem::CoupleTrains( AFGRailroadVehicle* parentVehicle, AFGRailroadVehicle* otherVehicle ){ }
void AFGRailroadSubsystem::DecoupleTrains( AFGRailroadVehicle* firstVehicle, AFGRailroadVehicle* secondVehicle ){ }
bool AFGRailroadSubsystem::GetTrainData( int32 trainID, FTrainData& out_trainData ){ return bool(); }
void AFGRailroadSubsystem::GetTrainOrder( int32 trainID,  AFGRailroadVehicle*& out_firstVehicle,  AFGRailroadVehicle*& out_lastVehicle ){ }
UFGRailroadTimeTable* AFGRailroadSubsystem::FindTimeTable( int32 trainID ) const{ return nullptr; }
UFGRailroadTimeTable* AFGRailroadSubsystem::FindOrAddTimeTable( int32 trainID ){ return nullptr; }
void AFGRailroadSubsystem::SetTrainSelfDrivingEnabled( int32 trainID, bool isEnabled ){ }
bool AFGRailroadSubsystem::IsTrainSelfDrivingEnabled( int32 trainID ) const{ return bool(); }
FRailroadPathFindingResult AFGRailroadSubsystem::FindPathSync(  AFGLocomotive* locomotive,  AFGBuildableRailroadStation* stop ){ return FRailroadPathFindingResult(); }
AFGLocomotive* AFGRailroadSubsystem::GetTrainMultipleUnitMaster( int32 trainID ) const{ return nullptr; }
bool AFGRailroadSubsystem::SetTrainMultipleUnitMaster( int32 trainID,  AFGLocomotive* locomotive, bool force ){ return bool(); }
bool AFGRailroadSubsystem::CanSetTrainMultipleUnitMaster( int32 trainID, const  AFGLocomotive* locomotive ) const{ return bool(); }
FText AFGRailroadSubsystem::GenerateTrainStopName() const{ return FText(); }
bool AFGRailroadSubsystem::IsTrainStopNameAvailable( const FString& name ) const{ return bool(); }
void AFGRailroadSubsystem::AddTrainStop(  AFGBuildableRailroadStation* stop ){ }
void AFGRailroadSubsystem::RemoveTrainStop(  AFGBuildableRailroadStation* stop ){ }
void AFGRailroadSubsystem::GetTrainStops( TArray<  AFGBuildableRailroadStation* >& out_stops ) const{ }
float AFGRailroadSubsystem::MoveTrackPosition(  FRailroadTrackPosition& position, float delta ){ return float(); }
void AFGRailroadSubsystem::AddTrack(  AFGBuildableRailroadTrack* track ){ }
void AFGRailroadSubsystem::RemoveTrack(  AFGBuildableRailroadTrack* track ){ }
void AFGRailroadSubsystem::TickTrains( float dt ){ }
void AFGRailroadSubsystem::TickTrackGraphs( float dt ){ }
void AFGRailroadSubsystem::InitializeStationNames(){ }
AFGRailroadVehicle* AFGRailroadSubsystem::SpawnTrainInternal( TSubclassOf<  AFGRailroadVehicle > vehicleClass, const  FRailroadTrackPosition& trackPosition ){ return nullptr; }
int32 AFGRailroadSubsystem::RegisterTrain(  AFGRailroadVehicle* vehicle ){ return int32(); }
int32 AFGRailroadSubsystem::GenerateUniqueTrainID(){ return int32(); }
EGraphAStarResult AFGRailroadSubsystem::FindPathSyncInternal( const FRailroadTrackPosition& start,
											const FRailroadTrackPosition& end,
											TArray< FRailroadGraphAStarPathPoint >& out_pathPoints ) const{ return EGraphAStarResult(); }
void AFGRailroadSubsystem::OnTrainOrderChanged( int32 trainID ){ }
UFGRailroadVehicleSoundComponent* AFGRailroadSubsystem::CreateSoundComponentFor(  AFGRailroadVehicle* vehicle ){ return nullptr; }
void AFGRailroadSubsystem::OnMultipleUnitChanged( int32 trainID ){ }
void AFGRailroadSubsystem::MergeTrackGraphs( int32 first, int32 second ){ }
int32 AFGRailroadSubsystem::CreateTrackGraph(){ return int32(); }
void AFGRailroadSubsystem::RemoveTrackGraph( int graphID ){ }
void AFGRailroadSubsystem::AddTrackToGraph(  AFGBuildableRailroadTrack* track, int32 graphID ){ }
int32 AFGRailroadSubsystem::GenerateUniqueTrackGraphID(){ return int32(); }