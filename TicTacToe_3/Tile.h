// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EColor.h"
#include "Tile.generated.h"

class AChessPiece;
UCLASS()
class CHESSAI_3_API ATile : public AActor
{
	GENERATED_BODY()

public:
	struct s_Move {
		AChessPiece* piece;
		ATile* targetTile;
		int score;
	};
	// Sets default values for this actor's properties
	ATile();
	virtual void Tick(float DeltaTime) override;
	int getX() const;
	int getY() const;
	UFUNCTION(BlueprintCallable)
	EColor getColor() const;
	UFUNCTION(BlueprintCallable)
	void AcceptPiece();
	void HighlightTile();
	UFUNCTION(BlueprintCallable)
	void MakeAIMove();
	UFUNCTION(BlueprintCallable)
	void MakeAIMove2();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	int m_x;

	UPROPERTY(EditAnywhere)
	int m_y;

	class ABoard* m_board;



	UPROPERTY(EditAnywhere)
	EColor m_color;



};
