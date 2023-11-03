// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "ChessPiece.h"
#include "Bishop.h"
#include "Soldier.h"
#include "Queen.h"
#include "Knight.h"
#include "Rook.h"
#include "King.h"
//#include "EngineUtils.h"

ABoard::ABoard()
{
    m_board = TArray<ATile*>();
    m_pieces = TArray<AChessPiece*>();
    /**
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> BlackMaterial(TEXT("/Script/Engine.Material'/Game//Assets/Materials/Black.Black'"));
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> WhiteMaterial(TEXT("/Script/Engine.Material'/Game/Assets/Materials/White.White'"));
    m_black_Material = UMaterialInstanceDynamic::Create(BlackMaterial.Object, this);
    m_white_Material = UMaterialInstanceDynamic::Create(WhiteMaterial.Object, this);
    **/

}

void ABoard::BeginPlay()
{
    Super::BeginPlay();
    TArray<AActor*> FoundActors;
    UWorld* world = GetWorld();
    UGameplayStatics::GetAllActorsOfClass(world, ATile::StaticClass(), FoundActors);
    for (AActor* Actor : FoundActors)
    {
        ATile* Tile = Cast<ATile>(Actor);
        if (Tile)
        {
            m_board.Add(Tile);
        }

    }
    initTiles();
    updatePieces();
    TArray<AActor*> FoundKings;
    UGameplayStatics::GetAllActorsOfClass(world, AKing::StaticClass(), FoundKings);
    for (AActor* king : FoundKings)
    {
        AKing* king_piece = dynamic_cast<AKing*>(king);
        if(king_piece && king_piece->getColor() == EColor::Black)
        {
            m_black_king = king_piece;
        }
        if (king_piece && king_piece->getColor() == EColor::White)
        {
            m_white_king = king_piece;
        }
    }
}

void ABoard::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

ATile* ABoard::GetTile(int x, int y) const
{

    for (ATile* Tile : m_board)
    {
        if ((Tile->getX() == x) && (Tile->getY() == y))
        {
            return Tile;
        }
    }
    return nullptr;
}

AChessPiece* ABoard::GetPiece(int x, int y) const
{
    for (AChessPiece* piece : m_pieces)
    {
        if ((piece->getX() == x) && (piece->getY() == y))
        {
            return piece;
        }
    }
    return nullptr;
}

bool ABoard::hasPiece(int x, int y) const
{
    if (GetPiece(x, y))
    {
        return true;
    }
    return false;
}

void ABoard::updatePieces()
{
    m_pieces = TArray<AChessPiece*>{};
    UWorld* world = GetWorld();
    TArray<AActor*> FoundActors2;
    UGameplayStatics::GetAllActorsOfClass(world, AChessPiece::StaticClass(), FoundActors2);
    for (AActor* Actor2 : FoundActors2)
    {
        AChessPiece* piece = Cast<AChessPiece>(Actor2);
        if (piece)
        {
            m_pieces.Add(piece);
        }

    }
}

void ABoard::initTiles()
{
    for (ATile* tile : m_board)
    {
        UStaticMeshComponent* Root = Cast<UStaticMeshComponent>(tile->GetRootComponent());
        if (tile->getColor() == EColor::White)
        {
            // Create or get the white material
            UMaterial* WhiteMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game//Assets/Materials/White.White'"));

            // Apply the material to the tile's mesh
            if (WhiteMaterial)
            {
                Root->SetMaterial(0, WhiteMaterial);
            }
        }
        else if (tile->getColor() == EColor::Black)
        {
            // Create or get the black material
            UMaterial* BlackMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game//Assets/Materials/Black.Black'"));

            // Apply the material to the tile's mesh
            if (BlackMaterial)
            {
                Root->SetMaterial(0, BlackMaterial);
            }
        }

    }
}

void ABoard::setActivePiece(AChessPiece* piece)
{
    m_active_piece = piece;
}

AChessPiece* ABoard::getActivePiece() const
{
    return m_active_piece;
}

AKing* ABoard::getWhiteKing() const
{
    return m_white_king;
}

AKing* ABoard::getBlackKing() const
{
    return m_black_king;
}

TArray<AChessPiece*> ABoard::GetPieces() const
{
    return m_pieces;
}

TArray<ATile*> ABoard::GetTiles()
{
    return m_board;
}

int ABoard::rankBoard(TArray<AChessPiece*> c_pieces) const
{
    int rank = 0;

    if (m_black_king->CheckSquareForCheck(m_black_king->getX(), m_black_king->getY(), EColor::Black))
    {
        rank -= 5;
    }
    if (m_black_king->CheckSquareForCheck(m_black_king->getX(), m_black_king->getY(), EColor::Black) && (colorHasNoMoves(EColor::Black)))
    {
        rank -= 300;
    }
    if (m_white_king->CheckSquareForCheck(m_white_king->getX(), m_white_king->getY(), EColor::White))
    {
        rank += 5;
    }
    if (m_white_king->CheckSquareForCheck(m_white_king->getX(), m_white_king->getY(), EColor::White) && (colorHasNoMoves(EColor::White)))
    {
        rank += 300;
    }
    for (AChessPiece* piece : GetPieces())
    {
        if (piece->getColor() == EColor::Black)
        {
            ASoldier* pawn = dynamic_cast<ASoldier*>(piece);
            AKing* king = dynamic_cast<AKing*>(piece);
            if (!king)
            {
                if ((piece->getX() == 3 || piece->getX() == 4) && (piece->getY() == 3 || piece->getY() == 4))
                {
                    rank += 10;
                }
                else if (piece->getX() > 1 && piece->getX() < 7 && piece->getY() > 1 && piece->getY() < 7)
                {
                    rank += 3;
                }
                else if (piece->getX() > 0 && piece->getX() < 8 && piece->getY() > 0 && piece->getY() < 8)
                {
                    rank += 1;
                }
            }
        }
    }
    if (c_pieces.Num() > 0)
    {
        for (AChessPiece* piece : c_pieces)
        {
            if (piece != nullptr)
            {
                if (piece->getColor() == EColor::Black)
                {
                    ASoldier* pawn = dynamic_cast<ASoldier*>(piece);
                    AKnight* knight = dynamic_cast<AKnight*>(piece);
                    ARook* rook = dynamic_cast<ARook*>(piece);
                    ABishop* bishop = dynamic_cast<ABishop*>(piece);
                    AQueen* queen = dynamic_cast<AQueen*>(piece);
                    if (pawn)
                    {
                        rank -= 10;
                    }
                    if (knight)
                    {
                        rank -= 25;
                    }
                    if (bishop)
                    {
                        rank -= 25;
                    }
                    if (rook)
                    {
                        rank -= 30;
                    }
                    if (queen)
                    {
                        rank -= 100;
                    }
                }
                if (piece->getColor() == EColor::White)
                {
                    ASoldier* pawn = dynamic_cast<ASoldier*>(piece);
                    AKnight* knight = dynamic_cast<AKnight*>(piece);
                    ARook* rook = dynamic_cast<ARook*>(piece);
                    ABishop* bishop = dynamic_cast<ABishop*>(piece);
                    AQueen* queen = dynamic_cast<AQueen*>(piece);
                    if (pawn)
                    {
                        rank += 10;
                    }
                    if (knight)
                    {
                        rank += 25;
                    }
                    if (bishop)
                    {
                        rank += 25;
                    }
                    if (rook)
                    {
                        rank += 30;
                    }
                    if (queen)
                    {
                        rank += 100;
                    }
                }
            }          
        }
    }
    //UE_LOG(LogTemp, Warning, TEXT("---------"));
    return rank;
}

bool ABoard::colorHasNoMoves(EColor color) const
{
    TArray<ATile*> moves = TArray<ATile*>{};
    for (AChessPiece* piece : GetPieces())
    {
        if (piece->getColor() == color)
        {
            for (ATile* move : piece->GetPossibleMoves())
            {
                moves.Add(move);
            }
        }
    }
    if (moves.Num() == 0)
    {
        return true;
    }
    return false;
}

