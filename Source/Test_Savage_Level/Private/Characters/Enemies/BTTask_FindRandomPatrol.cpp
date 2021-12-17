// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/BTTask_FindRandomPatrol.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemies/Enemy.h"

UBTTask_FindRandomPatrol::UBTTask_FindRandomPatrol(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Find Random Patrol";
}

EBTNodeResult::Type UBTTask_FindRandomPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemy* controlledPawn = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());

	if (!controlledPawn)
		return EBTNodeResult::Failed;

	controlledPawn->UpdateWalkSpeed(PatrolSpeed);

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSys)
		return EBTNodeResult::Failed;

	UBlackboardComponent* blackboardComponent = OwnerComp.GetAIOwner()->GetBlackboardComponent();

	if (!blackboardComponent)
		return EBTNodeResult::Failed;

	FVector Result;
	if (FindRandomReachablePoint(controlledPawn->GetActorLocation(), Result))
		blackboardComponent->SetValueAsVector(BlackboardKey.SelectedKeyName, Result);
	else
		blackboardComponent->SetValueAsVector(BlackboardKey.SelectedKeyName, controlledPawn->GetActorLocation());

	return EBTNodeResult::Succeeded;
}

FString UBTTask_FindRandomPatrol::GetStaticDescription() const
{
	return FString::Printf(TEXT("Find Random Patrol"));
}

bool UBTTask_FindRandomPatrol::FindRandomReachablePoint(FVector Origin, FVector& Result)
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSys)
		return false;

	return NavSys->K2_GetRandomReachablePointInRadius(GetWorld(), Origin, Result, PatrolRadius);
}