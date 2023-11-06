// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"
#include "Board.h"
#include "Soldier.h"

TArray<ATile*> AKing::GetPossibleMoves()
{
	TArray<ATile*> p_moves = TArray<ATile*>();
	int og_x = m_x;
	int og_y = m_y;
	if (!(m_board->hasPiece(m_x + 1, m_y + 1)) || m_board->GetPiece(m_x + 1, m_y + 1)->getColor() != m_color)
	{
		if (inBorder(m_x + 1, m_y + 1))
		{
			p_moves.Add(m_board->GetTile(m_x + 1, m_y + 1));
		}	

	}
	if (!(m_board->hasPiece(m_x + 1, m_y - 1)) || m_board->GetPiece(m_x + 1, m_y - 1)->getColor() != m_color)
	{
		if (inBorder(m_x + 1, m_y - 1))
		{
			p_moves.Add(m_board->GetTile(m_x + 1, m_y - 1));
		}
	}
	if (!(m_board->hasPiece(m_x - 1, m_y + 1)) || m_board->GetPiece(m_x - 1, m_y + 1)->getColor() != m_color)
	{
		if (inBorder(m_x - 1, m_y + 1))
		{
			p_moves.Add(m_board->GetTile(m_x - 1, m_y + 1));
		}
	}
	if (!(m_board->hasPiece(m_x - 1, m_y - 1)) || m_board->GetPiece(m_x - 1, m_y - 1)->getColor() != m_color)
	{
		if (inBorder(m_x - 1, m_y - 1))
		{
			p_moves.Add(m_board->GetTile(m_x - 1, m_y - 1));
		}
	}
	if (!(m_board->hasPiece(m_x + 1, m_y)) || m_board->GetPiece(m_x + 1, m_y)->getColor() != m_color)
	{
		if (inBorder(m_x + 1, m_y))
		{
			p_moves.Add(m_board->GetTile(m_x + 1, m_y));
		}
	}
	if (!(m_board->hasPiece(m_x, m_y - 1)) || m_board->GetPiece(m_x, m_y - 1)->getColor() != m_color)
	{
		if (inBorder(m_x, m_y - 1))
		{
			p_moves.Add(m_board->GetTile(m_x, m_y - 1));
		}
	}
	if (!(m_board->hasPiece(m_x - 1, m_y)) || m_board->GetPiece(m_x - 1, m_y)->getColor() != m_color)
	{
		if (inBorder(m_x - 1, m_y))
		{
			p_moves.Add(m_board->GetTile(m_x - 1, m_y));
		}
	}
	if (!(m_board->hasPiece(m_x, m_y + 1)) || m_board->GetPiece(m_x, m_y + 1)->getColor() != m_color)
	{
		if (inBorder(m_x, m_y + 1))
		{
			p_moves.Add(m_board->GetTile(m_x, m_y + 1));
		}
	}
	//return p_moves;
	TArray<ATile*> f_moves = TArray<ATile*>();
	for (ATile* move : p_moves)
	{
		/**
		if (m_board->hasPiece(move->getX(), move->getY()))
		{
			if (move && !(CheckSquareForCheckSkipPiece(move->getX(), move->getY(), m_color, m_board->GetPiece(move->getX(), move->getY()))))
			{
				f_moves.Add(move);
			}
		}
		else**/
		if (move && !(CheckSquareForCheck(move->getX(), move->getY(), m_color)))
		{
			f_moves.Add(move);
		}
		this->setX(og_x);
		this->setY(og_y);
	}
	return f_moves;
}
bool AKing::CheckSquareForCheckSkipPiece(int x, int y, EColor color, AChessPiece* skipped_piece)
{
	bool bcheck = false;
	this->setX(x);
	this->setY(y);

	int og_x = skipped_piece->getX();
	int og_y = skipped_piece->getY();
	skipped_piece->setX(9);
	skipped_piece->setY(9);
	for (AChessPiece* piece : m_board->GetPieces())
	{
		if (piece->getColor() != color)
		{
			ASoldier* pawn = dynamic_cast<ASoldier*>(piece);
			if (pawn)
			{
				TArray<ATile*> piece_moves = pawn->GetAttackingMoves();
				for (ATile* move : piece_moves)
				{
					if (move->getX() == x && move->getY() == y)
					{
						bcheck = true;
					}
				}
			}
			else
			{
				TArray<ATile*> piece_moves = piece->GetPossibleMovesPrimitive();
				if (piece_moves.Num() > 0)
				{
					for (ATile* move : piece_moves)
					{
						if (move->getX() == x && move->getY() == y)
						{
							bcheck = true;
						}
					}
				}
			}
		}
	}
	skipped_piece->setX(og_x);
	skipped_piece->setY(og_y);
	return bcheck;
}


bool AKing::CheckSquareForCheck(int x, int y, EColor color)
{

	AChessPiece* skipped_piece = m_board->GetPiece(x, y);
	bool bcheck = false;

	this->setX(x);
	this->setY(y);
	if (skipped_piece)
	{
		skipped_piece->setX(100);
		skipped_piece->setY(100);
	}
	for (AChessPiece* piece : m_board->GetPieces())
	{
		if (piece->getX() == 100 && piece->getY() == 100)
		{
			continue;
		}
		if (piece->getColor() != color)
		{
			ASoldier* pawn = dynamic_cast<ASoldier*>(piece);
			if (pawn)
			{
				TArray<ATile*> piece_moves = pawn->GetAttackingMoves();
				for (ATile* move : piece_moves)
				{
					if (move->getX() == x && move->getY() == y)
					{
						bcheck = true;
					}
				}
			}
			else
			{
				TArray<ATile*> piece_moves = piece->GetPossibleMovesPrimitive();
				for (ATile* move : piece_moves)
				{
					if (move)
					{
						if (move->getX() == x && move->getY() == y)
						{
							bcheck = true;
						}
					}
				}
				
			}
		}
	}
	if (skipped_piece)
	{
		skipped_piece->setX(x);
		skipped_piece->setY(y);
	}
	return bcheck;
}

bool AKing::CheckSquareForCheckSkip(int x, int y, EColor color, int skip_x, int skip_y)
{
	bool bcheck = false;
	this->setX(x);
	this->setY(y);

	for (AChessPiece* piece : m_board->GetPieces())
	{
		if (piece->getX() == skip_x && piece->getY() == skip_y)
		{
			continue;
		}
		if (piece->getX() == x && piece->getY() == y)
		{
			continue;
		}
		if (piece->getColor() != color)
		{
			ASoldier* pawn = dynamic_cast<ASoldier*>(piece);
			if (pawn)
			{
				TArray<ATile*> piece_moves = pawn->GetAttackingMoves();
				for (ATile* move : piece_moves)
				{
					if (move->getX() == x && move->getY() == y)
					{
						bcheck = true;
					}
				}
			}
			else
			{
				TArray<ATile*> piece_moves = piece->GetPossibleMovesPrimitive();
				for (ATile* move : piece_moves)
				{
					if (move)
					{
						if (move->getX() == x && move->getY() == y)
						{
							bcheck = true;
						}
					}
				}

			}
		}
	}
	return bcheck;
}

TArray<ATile*> AKing::GetPossibleMovesPrimitive() const
{
	TArray<ATile*> p_moves = TArray<ATile*>();
	if (!(m_board->hasPiece(m_x + 1, m_y + 1)) || m_board->GetPiece(m_x + 1, m_y + 1)->getColor() != m_color)
	{
		if (inBorder(m_x + 1, m_y + 1))
		{
			p_moves.Add(m_board->GetTile(m_x + 1, m_y + 1));
		}

	}
	if (!(m_board->hasPiece(m_x + 1, m_y - 1)) || m_board->GetPiece(m_x + 1, m_y - 1)->getColor() != m_color)
	{
		if (inBorder(m_x + 1, m_y - 1))
		{
			p_moves.Add(m_board->GetTile(m_x + 1, m_y - 1));
		}
	}
	if (!(m_board->hasPiece(m_x - 1, m_y + 1)) || m_board->GetPiece(m_x - 1, m_y + 1)->getColor() != m_color)
	{
		if (inBorder(m_x - 1, m_y + 1))
		{
			p_moves.Add(m_board->GetTile(m_x - 1, m_y + 1));
		}
	}
	if (!(m_board->hasPiece(m_x - 1, m_y - 1)) || m_board->GetPiece(m_x - 1, m_y - 1)->getColor() != m_color)
	{
		if (inBorder(m_x - 1, m_y - 1))
		{
			p_moves.Add(m_board->GetTile(m_x - 1, m_y - 1));
		}
	}
	if (!(m_board->hasPiece(m_x + 1, m_y)) || m_board->GetPiece(m_x + 1, m_y)->getColor() != m_color)
	{
		if (inBorder(m_x + 1, m_y))
		{
			p_moves.Add(m_board->GetTile(m_x + 1, m_y));
		}
	}
	if (!(m_board->hasPiece(m_x, m_y - 1)) || m_board->GetPiece(m_x, m_y - 1)->getColor() != m_color)
	{
		if (inBorder(m_x, m_y - 1))
		{
			p_moves.Add(m_board->GetTile(m_x, m_y - 1));
		}
	}
	if (!(m_board->hasPiece(m_x - 1, m_y)) || m_board->GetPiece(m_x - 1, m_y)->getColor() != m_color)
	{
		if (inBorder(m_x - 1, m_y))
		{
			p_moves.Add(m_board->GetTile(m_x - 1, m_y));
		}
	}
	if (!(m_board->hasPiece(m_x, m_y + 1)) || m_board->GetPiece(m_x, m_y + 1)->getColor() != m_color)
	{
		if (inBorder(m_x, m_y + 1))
		{
			p_moves.Add(m_board->GetTile(m_x, m_y + 1));
		}
	}
	return p_moves;

}
