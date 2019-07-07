// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGWheeledVehicle.h"

void AFGWheeledVehicle::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const{ }
AFGWheeledVehicle::AFGWheeledVehicle(){ }
void AFGWheeledVehicle::PostInitializeComponents(){ }
void AFGWheeledVehicle::BeginPlay(){ }
void AFGWheeledVehicle::Destroyed(){ }
void AFGWheeledVehicle::Tick( float dt ){ }
void AFGWheeledVehicle::DisplayDebug( UCanvas* canvas, const FDebugDisplayInfo& debugDisplay, float& YL, float& YPos){ }
bool AFGWheeledVehicle::CanDock_Implementation( EDockStationType atStation ) const{ return bool(); }
UFGInventoryComponent* AFGWheeledVehicle::GetDockInventory_Implementation() const{ return nullptr; }
UFGInventoryComponent* AFGWheeledVehicle::GetDockFuelInventory_Implementation() const{ return nullptr; }
void AFGWheeledVehicle::WasDocked_Implementation(  AFGBuildableDockingStation* atStation ){ }
void AFGWheeledVehicle::WasUndocked_Implementation(){ }
void AFGWheeledVehicle::OnBeginLoadVehicle_Implementation(){ }
void AFGWheeledVehicle::OnBeginUnloadVehicle_Implementation(){ }
void AFGWheeledVehicle::OnTransferComplete_Implementation(){ }
UWheeledVehicleMovementComponent* AFGWheeledVehicle::GetVehicleMovementComponent() const{ return nullptr; }
void AFGWheeledVehicle::SetMovementComponent( UWheeledVehicleMovementComponent* movementComponent ){ }
bool AFGWheeledVehicle::HasFuel(){ return bool(); }
void AFGWheeledVehicle::GetTireData( TArray< FTireData >& out_tireData ){ }
UParticleSystem* AFGWheeledVehicle::GetSurfaceParticleSystem( UPhysicalMaterial* physMat){ return nullptr; }
float AFGWheeledVehicle::GetForwardSpeed(){ return float(); }
bool AFGWheeledVehicle::IsValidFuel( TSubclassOf<  UFGItemDescriptor > resource ) const{ return bool(); }
void AFGWheeledVehicle::HandleDestroyStaticMesh( AActor* actor, float forceOfCollision ){ }
void AFGWheeledVehicle::HandleDestroyFoliage(){ }
bool AFGWheeledVehicle::FilterFuelClasses( TSubclassOf< UObject > object, int32 idx ) const{ return bool(); }
void AFGWheeledVehicle::SimulateDSOLGearBox( float DeltaTime,
									 float RawThrottleInput,
									 DSOLSetupData& setupData,
									 DSOLDynGearboxData& gearboxData, 
									 PxVehicleWheelsSimData& wheelsSimData, 
									 PxVehicleDriveDynData& driveDynData, 
									 PxVehicleDriveSimData& driveSimData ){ }
void AFGWheeledVehicle::SetSimulation( bool newIsSimulating ){ }
bool AFGWheeledVehicle::WantsToMove(){ return bool(); }
float AFGWheeledVehicle::GetFuelBurnRatio(){ return float(); }
UFGTargetPointLinkedList* AFGWheeledVehicle::GetTargetNodeLinkedList(){ return nullptr; }
void AFGWheeledVehicle::RemoveTargetPoint(  AFGTargetPoint* targetToRemove ){ }
void AFGWheeledVehicle::SetPathFromArray( TArray<  AFGTargetPoint* > targetPoints ){ }
//void AFGWheeledVehicle::PlayFoliageDestroyedEffect(  UParticleSystem* destroyEffect,  UAkAudioEvent* destroyAudioEvent, FVector location ){ }
void AFGWheeledVehicle::OnOverlapBegin( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult ){ }
void AFGWheeledVehicle::OnOverlapEnd( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex ){ }
void AFGWheeledVehicle::ManageFakeForces( float DeltaTime ){ }
void AFGWheeledVehicle::Died( AActor* thisActor ){ }
void AFGWheeledVehicle::CreateInventoryItemDrops_Implementation(){ }
void AFGWheeledVehicle::SetAddedAngularVelocityPitch( float pitchToAdd ){ }
void AFGWheeledVehicle::SetAddedAngularVelocityYaw( float yawToAdd ){ }
void AFGWheeledVehicle::ResetAddedAngularVelocityValues(){ }
void AFGWheeledVehicle::UpdateAssistedVelocitiesState(){ }
void AFGWheeledVehicle::ServerUpdateAssistedVelocitiesState_Implementation( bool inDrifting, float inInputYaw, float inInputPitch ){ }
bool AFGWheeledVehicle::ServerUpdateAssistedVelocitiesState_Validate( bool inDrifting, float inInputYaw, float inInputPitch ){ return bool(); }
void AFGWheeledVehicle::UseReplicatedState(){ }
void AFGWheeledVehicle::UpdateSimulationState(){ }
void AFGWheeledVehicle::UpdateAirStatus(){ }
void AFGWheeledVehicle::UpdateTireEffects(){ }
void AFGWheeledVehicle::UpdateTireParticle( FTireData tireData ){ }
void AFGWheeledVehicle::BurnFuel( float dt ){ }
void AFGWheeledVehicle::ApplyAddedAngularVelocityModifiers( float deltaTime ){ }
void AFGWheeledVehicle::SwitchParticle( int32 tireIndex, UParticleSystem* particleTemplate ){ }
void AFGWheeledVehicle::DrawTireTrack( FTireData tireData, FVector decalLocation ){ }
void AFGWheeledVehicle::OnSimulationChanged(){ }
void AFGWheeledVehicle::ClampVelocities(){ }
void AFGWheeledVehicle::AddedLinearThrottleVelocity(){ }
void AFGWheeledVehicle::ApplyRollStabilisation( float deltaTime ){ }
void AFGWheeledVehicle::ApplyAssistedVelocities( float deltaTime ){ }
void AFGWheeledVehicle::OnRep_IsSimulated(){ }
void AFGWheeledVehicle::OnRep_TransferStatusChanged(){ }
