// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPiece.h"
#include "Tile.h"
#include "King.h"
#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Board.h"
//#include "EngineUtils.h"

// Sets default values
AChessPiece::AChessPiece()
{
    m_x = 0;
    m_y = 0;
    m_color = EColor::White;

    GameModeRef1 = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    //m_board = Cast<ABoard>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoard::StaticClass()));
    /**
    for (TActorIterator<ATile> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        ATile* Instance = *ActorItr;
        if (Instance)
        {
            // Add the instance to the TArray
            m_board.Add(Instance);
        }
    }
    **/
}

// Called when the game starts or when spawned
void AChessPiece::BeginPlay()
{
    Super::BeginPlay();
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoard::StaticClass(), FoundActors);
    m_board = Cast<ABoard>(FoundActors[0]);

}

TArray<ATile*> AChessPiece::GetPossibleMoves()
{
    return TArray<ATile*>();
}

void AChessPiece::PieceClicked()
{
    if (getColor() == EColor::White)
    {
        if (m_board->colorHasNoMoves(m_color))
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StaleMate! Game Over"));
        }
        m_board->initTiles();
        m_board->setActivePiece(this);
        bool bisActiveKinginCheck = false;
        AKing* ActiveKing = m_board->getWhiteKing();
        if (getColor() == EColor::White)
        {
            ActiveKing = m_board->getWhiteKing();
            bisActiveKinginCheck = ActiveKing->CheckSquareForCheck(ActiveKing->getX(), ActiveKing->getY(), EColor::White);
        }
        if (!bisActiveKinginCheck)
        {
            for (ATile* tile : GetPossibleMoves())
            {
                tile->HighlightTile();
            }
        }
        if (bisActiveKinginCheck)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("White King is in Check"));
            TArray<ATile*> validTiles = TArray<ATile*>();
            TArray<ATile*> tempTiles = GetPossibleMoves();
            for (ATile* tile : tempTiles)
            {
                int og_x = getX();
                int og_y = getY();
                setX(tile->getX());
                setY(tile->getY());
                if (!(ActiveKing->CheckSquareForCheckSkip(ActiveKing->getX(), ActiveKing->getY(), ActiveKing->getColor(), tile->getX(), tile->getY())))
                {
                    validTiles.Add(tile);
                }
                setX(og_x);
                setY(og_y);
            }
            if (m_board->colorHasNoMoves(m_color))
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CheckMate! Game Over"));
            }
            for (ATile* tile : validTiles)
            {
                tile->HighlightTile();
            }
        }
    }

}

// Called every frame
void AChessPiece::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

int AChessPiece::getX() const
{
    return m_x;
}
int AChessPiece::getY() const
{
    return m_y;
}

void AChessPiece::setX(int x)
{
    m_x = x;
}
void AChessPiece::setY(int y)
{
    m_y = y;
}

bool AChessPiece::inBorder(int x, int y) const
{
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
    {
        return true;
    }
    return false;
}

TArray<ATile*> AChessPiece::filterForNoCheck(TArray<ATile*> tiles, EColor color)
{
    int og_x = getX();
    int og_y = getY();

    TArray<ATile*> f_tiles = TArray<ATile*>();
    AKing* king = m_board->getWhiteKing();
    if (color == EColor::Black)
    {
        king = m_board->getBlackKing();
    }
    for (ATile* tile : tiles)
    {
        if (tile)
        {
            this->setX(tile->getX());
            this->setY(tile->getY());
            if (!(king->CheckSquareForCheckSkip(king->getX(), king->getY(), color, tile->getX(), tile->getY())))
            {
                f_tiles.Add(tile);
            }
            this->setX(og_x);
            this->setY(og_y);
        }
    }
    return f_tiles;
}

EColor AChessPiece::getColor() const
{
    return m_color;
}

TArray<ATile*> AChessPiece::GetPossibleMovesPrimitive() const
{
    return TArray<ATile*>();
}
