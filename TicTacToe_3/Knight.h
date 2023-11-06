// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPiece.h"
#include "Knight.generated.h"

/**
 * 
 */
UCLASS()
class CHESSAI_3_API AKnight : public AChessPiece
{
	GENERATED_BODY()
	TArray<ATile*> GetPossibleMoves() override;
	TArray<ATile*> GetPossibleMovesPrimitive() const override;
	
};
