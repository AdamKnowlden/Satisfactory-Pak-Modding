// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGCharacterMovementComponent.h"

UFGCharacterMovementComponent::UFGCharacterMovementComponent(){ }
void UFGCharacterMovementComponent::TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction ){ }
FNetworkPredictionData_Client* UFGCharacterMovementComponent::GetPredictionData_Client() const{ return nullptr; }
bool UFGCharacterMovementComponent::DoJump( bool isReplayingMoves ){ return bool(); }
void UFGCharacterMovementComponent::CalcVelocity( float dt, float friction, bool isFluid, float brakingDeceleration ){ }
float UFGCharacterMovementComponent::GetMaxSpeed() const{ return float(); }
void UFGCharacterMovementComponent::SetDefaultMovementMode(){ }
void UFGCharacterMovementComponent::ServerSetHookLocation_Implementation( const FVector& hookLocation ){ }
bool UFGCharacterMovementComponent::ServerSetHookLocation_Validate( const FVector& hookLocation ){ return bool(); }
void UFGCharacterMovementComponent::SetHookLocation( const FVector& hookLocation){ }
void UFGCharacterMovementComponent::SetWantsToSprint( bool wantsToSprint ){ }
bool UFGCharacterMovementComponent::CanGrabLadder(  UFGLadderComponent* ladder ) const{ return bool(); }
void UFGCharacterMovementComponent::StartClimbLadder(  UFGLadderComponent* ladder ){ }
void UFGCharacterMovementComponent::StopClimbLadder(){ }
void UFGCharacterMovementComponent::JumpOffLadder(){ }
UFGLadderComponent* UFGCharacterMovementComponent::GetOnLadder() const{ return nullptr; }
void UFGCharacterMovementComponent::UpdateFromCompressedFlags(uint8 flags){ }
void UFGCharacterMovementComponent::OnMovementUpdated(float deltaSeconds, const FVector & oldLocation, const FVector & oldVelocity){ }
void UFGCharacterMovementComponent::OnMovementModeChanged( EMovementMode PreviousMovementMode, uint8 PreviousCustomMode ){ }
void UFGCharacterMovementComponent::PhysCustom( float deltaTime, int32 Iterations ){ }
void UFGCharacterMovementComponent::SetOnLadder(  UFGLadderComponent* ladder ){ }
void UFGCharacterMovementComponent::PhysLadder( float deltaTime, int32 iterations ){ }
void UFGCharacterMovementComponent::UpdateJetPack( float deltaSeconds ){ }
void UFGCharacterMovementComponent::UpdateHookshot( float deltaSeconds, FVector oldLocation ){ }
void UFGCharacterMovementComponent::UpdateSprintStatus( float delta ){ }
void UFGCharacterMovementComponent::UpdateParachute( float delta ){ }
void UFGCharacterMovementComponent::UpdateJumpingStilts( float deltaSeconds ){ }
bool UFGCharacterMovementComponent::CanSprint(){ return bool(); }
AFGJetPack* UFGCharacterMovementComponent::GetCachedJetPack(){ return nullptr; }
AFGHookshot* UFGCharacterMovementComponent::GetCachedHookshot(){ return nullptr; }
AFGParachute* UFGCharacterMovementComponent::GetCachedParachute(){ return nullptr; }
AFGJumpingStilts* UFGCharacterMovementComponent::GetCachedJumpingStilts(){ return nullptr; }
void FSavedMove_FGMovement::Clear(){ }
uint8 FSavedMove_FGMovement::GetCompressedFlags() const{ return uint8(); }
bool FSavedMove_FGMovement::CanCombineWith(const FSavedMovePtr& newMove, ACharacter* character, float maxDelta) const{ return bool(); }
void FSavedMove_FGMovement::SetMoveFor(ACharacter* character, float inDeltaTime, FVector const& newAccel,  FNetworkPredictionData_Client_Character & clientData){ }
void FSavedMove_FGMovement::PrepMoveFor( ACharacter* character){ }
FNetworkPredictionData_Client_FGMovement::FNetworkPredictionData_Client_FGMovement(const UCharacterMovementComponent& clientMovement) : FNetworkPredictionData_Client_Character(clientMovement) { }
FSavedMovePtr FNetworkPredictionData_Client_FGMovement::AllocateNewMove(){ return FSavedMovePtr(); }
