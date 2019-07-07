// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGBuildableConveyorBelt.h"

AFGBuildableConveyorBelt::AFGBuildableConveyorBelt(){ }
void AFGBuildableConveyorBelt::GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const{ }
void AFGBuildableConveyorBelt::BeginPlay(){ }
void AFGBuildableConveyorBelt::EndPlay( const EEndPlayReason::Type endPlayReason ){ }
bool AFGBuildableConveyorBelt::IsComponentRelevantForNavigation( UActorComponent* component ) const{ return bool(); }
void AFGBuildableConveyorBelt::GainedSignificance_Implementation(){ }
	void AFGBuildableConveyorBelt::LostSignificance_Implementation(){ }
void AFGBuildableConveyorBelt::UpdateUseState_Implementation(  AFGCharacterPlayer* byCharacter, const FVector& atLocation,  UPrimitiveComponent* componentHit, FUseState& out_useState ) const{ }
void AFGBuildableConveyorBelt::OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ){ }
void AFGBuildableConveyorBelt::OnUseStop_Implementation(AFGCharacterPlayer * byCharacter, const FUseState & state)
{
}
bool AFGBuildableConveyorBelt::IsUseable_Implementation() const{ return bool(); }
void AFGBuildableConveyorBelt::StartIsLookedAt_Implementation(  AFGCharacterPlayer* byCharacter, const FUseState& state  ){ }
void AFGBuildableConveyorBelt::StopIsLookedAt_Implementation(  AFGCharacterPlayer* byCharacter, const FUseState& state ){ }
FText AFGBuildableConveyorBelt::GetLookAtDecription_Implementation(  AFGCharacterPlayer* byCharacter, const FUseState& state ) const{ return FText(); }
float AFGBuildableConveyorBelt::FindOffsetClosestToLocation( const FVector& location ) const{ return float(); }
void AFGBuildableConveyorBelt::GetLocationAndDirectionAtOffset( float offset, FVector& out_location, FVector& out_direction ) const{ }
void AFGBuildableConveyorBelt::TogglePendingDismantleMaterial( bool enabled ){ }
FVector AFGBuildableConveyorBelt::GetVelocityForBase(  AActor* basedActor,  UPrimitiveComponent* baseComponent ) const{ return FVector(); }
FVector AFGBuildableConveyorBelt::GetRefundSpawnLocationAndArea_Implementation( const FVector& aimHitLocation, float& out_radius ) const{ return FVector(); }
void AFGBuildableConveyorBelt::Upgrade_Implementation( AActor* newActor ){ }
TArray< AFGBuildableConveyorBelt* > AFGBuildableConveyorBelt::Split( AFGBuildableConveyorBelt* conveyor, float offset ){ return TArray<AFGBuildableConveyorBelt* >(); }
AFGBuildableConveyorBelt* AFGBuildableConveyorBelt::Merge( TArray< AFGBuildableConveyorBelt* > conveyors ){ return nullptr; }
AFGBuildableConveyorBelt* AFGBuildableConveyorBelt::Respline( AFGBuildableConveyorBelt* conveyor, const TArray< FSplinePointData >& newSplineData ){ return nullptr; }
bool AFGBuildableConveyorBelt::VerifyDefaults( FString& out_message ){ return bool(); }
void AFGBuildableConveyorBelt::TickItemTransforms( float dt ){ }
