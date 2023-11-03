// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPiece.h"
#include "King.generated.h"

/**
 * 
 */
UCLASS()
class CHESSAI_3_API AKing : public AChessPiece
{
	GENERATED_BODY()

public:

	TArray<ATile*> GetPossibleMoves() override;
	bool CheckSquareForCheck(int x, int y, EColor color);
	bool CheckSquareForCheckSkip(int x, int y, EColor color, int skip_x, int skip_y);
	bool CheckSquareForCheckSkipPiece(int x, int y, EColor color, AChessPiece* skipped_piece);
	TArray<ATile*> GetPossibleMovesPrimitive() const override;
	
};
