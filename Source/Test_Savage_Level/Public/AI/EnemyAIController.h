// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

class APlayerCharacter;

#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TEST_SAVAGE_LEVEL_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void UpdateTargetPerception(AActor* Actor, FAIStimulus Stimulus);
	void LoseTrackOfPlayer();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBlackboardData* BlackboardData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree;

	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	// Determine how long before the AI gives up chasing the Player.
	float ChaseTimer = 5.f;
	FTimerHandle EnemyTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName HasLineOfSight = "HasLineOfSight";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName PlayerActor = "PlayerActor";
	FTimerManager* TimerManager;

	UPROPERTY(Category = EnemyAIController, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAIPerceptionComponent* AIPerceptionComponent;

	UAISenseConfig_Sight* SightConfig;

	APlayerCharacter* PlayerCharacter;
};
