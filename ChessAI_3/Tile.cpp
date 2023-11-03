// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "ChessPiece.h"
#include "Soldier.h"
#include "King.h"
#include "Queen.h"
#include "Board.h"
#include "Engine/StaticMesh.h"




// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoard::StaticClass(), FoundActors);
	m_board = Cast<ABoard>(FoundActors[0]);

}

int ATile::getX() const
{
	return m_x;
}

int ATile::getY() const
{
	return m_y;
}

EColor ATile::getColor() const
{
	return m_color;
}

void ATile::AcceptPiece()
{
	m_board->m_moves++;
	FString MovesCountMessage = FString::Printf(TEXT("Moves Count: %d"), m_board->m_moves);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *MovesCountMessage);
	if (m_board->m_moves > 199)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StaleMate! Game Over"));
	}
	AChessPiece* piece = m_board->getActivePiece();
	m_board->initTiles();
	if (m_board->hasPiece(getX(), getY()))
	{
		m_board->GetPiece(getX(), getY())->Destroy();
	}
	ASoldier* pawn = dynamic_cast<ASoldier*>(piece);
	if (pawn)
	{
		pawn->SetFirstMoveToFalse();
	}
	piece->setX(getX());
	piece->setY(getY());
	
	FName SocketName = "Socket";
	piece->AttachToComponent(GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false), SocketName);
	m_board->updatePieces();
}

void ATile::HighlightTile()
{
	UStaticMeshComponent* Root = Cast<UStaticMeshComponent>(GetRootComponent());
	UMaterial* PinkMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game//Assets/Materials/Pink.Pink'"));
	if (PinkMaterial)
	{
		Root->SetMaterial(0, PinkMaterial);
	}

}

void ATile::MakeAIMove()
{
	AKing* ActiveKing = m_board->getBlackKing();
	bool bisActiveKinginCheck = ActiveKing->CheckSquareForCheck(ActiveKing->getX(), ActiveKing->getY(), EColor::Black);
	if (bisActiveKinginCheck)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Black King is in Check"));
		if (m_board->colorHasNoMoves(m_color))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CheckMate! Game Over"));
		}
	}
	AChessPiece* chosen_piece = nullptr;
	ATile* chosen_tile = nullptr;
	int max_score = -10000;
	for (AChessPiece* piece : m_board->GetPieces())
	{
		if (piece->getColor() == EColor::Black)
		{
			TArray<ATile*> tiles = piece->GetPossibleMoves();
			for (ATile* tile : tiles)
			{
				TArray<AChessPiece*> Captured_Pieces = TArray<AChessPiece*>();
				if (m_board->hasPiece(tile->getX(), tile->getY()))
				{
					Captured_Pieces.Add(m_board->GetPiece(tile->getX(), tile->getY()));
				}	
				int og_x = piece->getX();
				int og_y = piece->getY();
				piece->setX(tile->getX());
				piece->setY(tile->getY());
				if (m_board->rankBoard(Captured_Pieces) > max_score)
				{
					chosen_piece = piece;
					chosen_tile = tile;
					max_score = m_board->rankBoard(Captured_Pieces);
				}
				piece->setX(og_x);
				piece->setY(og_y);
			}
		}
	}
	if (max_score == -10000)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StaleMate! Game Over"));
		return;
	}
	m_board->setActivePiece(chosen_piece);
	chosen_tile->AcceptPiece();
	return;

}
void ATile::MakeAIMove2()
{
	AKing* ActiveKing = m_board->getBlackKing();
	bool bisActiveKinginCheck = ActiveKing->CheckSquareForCheck(ActiveKing->getX(), ActiveKing->getY(), EColor::Black);
	if (bisActiveKinginCheck)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Black King is in Check"));
		if (m_board->colorHasNoMoves(m_color))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CheckMate! Game Over"));
			return;
		}
	}
	AChessPiece* chosen_piece = nullptr;
	ATile* chosen_tile = nullptr;
	int max_score = -10000;
	TArray<s_Move> player_best_moves = TArray<s_Move>();
	for (AChessPiece* piece : m_board->GetPieces())
	{
		AChessPiece* captured_piece = nullptr;
		if (piece->getColor() == EColor::Black)
		{
			TArray<ATile*> tiles = piece->GetPossibleMoves();
			for (ATile* tile : tiles)
			{
				TArray<AChessPiece*> Captured_Pieces = TArray<AChessPiece*>();
				Captured_Pieces.Empty();
				if (m_board->hasPiece(tile->getX(), tile->getY()))
				{
					captured_piece = m_board->GetPiece(tile->getX(), tile->getY());
				}
				int og_x = piece->getX();
				int og_y = piece->getY();
				piece->setX(tile->getX());
				piece->setY(tile->getY());
				int min_score = 10000;
				for (AChessPiece* piece2 : m_board->GetPieces())
				{
					if (piece2->getX() == tile->getX() && piece2->getY() == tile->getY())
					{
						continue;
					}
					if (piece2->getColor() == EColor::White)
					{
						for (ATile* tile2 : piece2->GetPossibleMoves())
						{
							if (captured_piece)
							{
								Captured_Pieces.Add(captured_piece);
							}
							if (m_board->hasPiece(tile2->getX(), tile2->getY()))
							{
								Captured_Pieces.Add(m_board->GetPiece(tile2->getX(), tile2->getY()));
							}
							int og_x2 = piece2->getX();
							int og_y2 = piece2->getY();
							piece2->setX(tile2->getX());
							piece2->setY(tile2->getY());
							int current_score = m_board->rankBoard(Captured_Pieces);
							if (current_score < min_score)
							{
								min_score = current_score;
								chosen_tile = tile;
								chosen_piece = piece;
							}
							piece2->setX(og_x2);
							piece2->setY(og_y2);
							Captured_Pieces.Empty();
						}
					}
				}
				s_Move chosen_move;
				chosen_move.score = min_score;
				chosen_move.piece = chosen_piece;
				chosen_move.targetTile = chosen_tile;
				player_best_moves.Add(chosen_move);
				piece->setX(og_x);
				piece->setY(og_y);
			}
		}
	}
	TArray<s_Move> chosen_moves = TArray<s_Move>();
	s_Move chosen_move = player_best_moves[0];
	for (ATile::s_Move move : player_best_moves)
	{
		if (move.score == max_score)
		{
			chosen_moves.Add(move);
		}
		if (move.score > max_score)
		{
			max_score = move.score;
			chosen_move = move;
			chosen_moves.Add(move);
		}
	}
	if (max_score == -10000)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StaleMate! Game Over"));
		return;
	}
	if (chosen_moves.Num() > 1)
	{
		int32 index = FMath::RandRange(0, chosen_moves.Num() - 1);
		m_board->setActivePiece(chosen_moves[index].piece);
		chosen_moves[index].targetTile->AcceptPiece();
		return;

	}
	m_board->setActivePiece(chosen_move.piece);
	chosen_move.targetTile->AcceptPiece();
	return;
}


// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

