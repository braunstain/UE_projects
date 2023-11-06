// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPiece.h"
#include "Soldier.generated.h"

/**
 *
 */
UCLASS()
class CHESSAI_3_API ASoldier : public AChessPiece
{
	GENERATED_BODY()

public:

	virtual void BeginPlay();
	TArray<ATile*> GetPossibleMoves() override;
	TArray<ATile*> GetPeacfulMoves() const;
	TArray<ATile*> GetAttackingMoves() const;
	TArray<ATile*> GetPossibleMovesPrimitive() const override;
	void SetFirstMoveToFalse();

private:
	bool b_first_move = true;
};
