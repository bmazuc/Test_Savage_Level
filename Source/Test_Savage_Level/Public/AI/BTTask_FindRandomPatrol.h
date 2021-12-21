// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindRandomPatrol.generated.h"

/**
 * 
 */
UCLASS()
class TEST_SAVAGE_LEVEL_API UBTTask_FindRandomPatrol : public UBTTaskNode
{
	GENERATED_BODY()
	
	UBTTask_FindRandomPatrol(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;

	bool FindRandomReachablePoint(FVector Origin, FVector& Result);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PatrolSpeed = 125.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PatrolRadius = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector BlackboardKey;
};
