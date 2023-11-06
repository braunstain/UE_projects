// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
//#include "ChessPiece.h"
#include "Kismet/GameplayStatics.h"
#include "Board.generated.h"

class AChessPiece;
class AKing;

UCLASS()
class CHESSAI_3_API ABoard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	ATile* GetTile(int x, int y) const;
	AChessPiece* GetPiece(int x, int y) const;
	bool hasPiece(int x, int y) const;
	void updatePieces();
	void initTiles();
	void setActivePiece(AChessPiece* piece);
	UFUNCTION(BlueprintCallable)
	AChessPiece* getActivePiece() const;
	AKing* getWhiteKing() const;
	AKing* getBlackKing() const;
	TArray<AChessPiece*> GetPieces() const;
	TArray<ATile*> GetTiles();
	int rankBoard(TArray<AChessPiece*> c_pieces) const;
	bool colorHasNoMoves(EColor color) const;
	int m_moves = 0;

private:
	TArray<ATile*> m_board;
	TArray<AChessPiece*> m_pieces;
	AChessPiece* m_active_piece;
	AKing* m_black_king;
	AKing* m_white_king;
};
