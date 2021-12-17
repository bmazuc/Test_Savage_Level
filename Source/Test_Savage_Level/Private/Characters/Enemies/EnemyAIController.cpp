// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/EnemyAIController.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree && BlackboardData)
	{
		UseBlackboard(BlackboardData, BlackboardComponent);
		RunBehaviorTree(BehaviorTree);
	}
}