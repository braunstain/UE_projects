// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Tile.h"
#include "Materials/Material.h"

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
	m_mesh = FindComponentByClass<UStaticMeshComponent>();
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATile::StaticClass(), m_board);
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EColor ATile::GetColor() const
{
	return m_color;

}

void ATile::SetColor(EColor new_color)
{
	m_color = new_color;

}

void ATile::setOptions()
{
	options_size = 0;
	for (int i = 0; i < 9; i++)
	{
		if (m_board[i]->GetColor() == EColor::White)
		{
			m_options.Add(m_board[i]);
			options_size++;
		}
	}

}

ATile* ATile::selectTile()
{
	ATile* bestTile = m_options[0];
	int bestScore = -1000;
	for (int i = 0; i < options_size; i++)
	{
		m_options[i]->SetColor(EColor::Blue);
		int lowScore = 1000;
		for (int j = 0; j < options_size; j++)
		{
			if (j != i)
			{
				m_options[j]->SetColor(EColor::Red);
				int current_score = m_options[j]->ScoreBoard();
				if (current_score < lowScore)
				{					
					lowScore = current_score;
				}
				m_options[j]->SetColor(EColor::White);
			}
		}
		if (lowScore > bestScore)
		{
			bestScore = lowScore;
			bestTile = m_options[i];
		}
		m_options[i]->SetColor(EColor::White);
	}
	return bestTile;
}

ATile* ATile::selectTile2()
{
	ATile* bestTile = m_options[0];
	int bestScore = -1000;
	ATile* lowTile = m_options[0];
	int chosen_j = 0;
	bool b_continue = false;
	for (int i = 0; i < options_size; i++)
	{
		b_continue = false;
		m_options[i]->SetColor(EColor::Blue);
		int lowScore = 1000;
		for (int j = 0; j < options_size; j++)
		{
			if (j != i)
			{
				m_options[j]->SetColor(EColor::Red);
				int current_score = m_options[j]->ScoreBoard();
				if (current_score == -500)
				{
					m_options[j]->SetColor(EColor::White);
					b_continue = true;
					break;
				}
				if (current_score < lowScore)
				{
					lowTile = m_options[j];
					lowScore = current_score;
					chosen_j = j;
				}
				m_options[j]->SetColor(EColor::White);
			}
		}
		if (b_continue)
		{
			m_options[i]->SetColor(EColor::White);
			continue;
		}
		if (options_size == 2 && lowScore > bestScore)
		{
			bestScore = lowScore;
			bestTile = m_options[i];
		}
		lowTile->SetColor(EColor::Red);
		for (int k = 0; k < options_size; k++)
		{
			if (k != i && k != chosen_j)
			{
				m_options[k]->SetColor(EColor::Blue);
				int final_score = m_options[k]->ScoreBoard();
				if (final_score > bestScore)
				{
					bestScore = final_score;
					bestTile = m_options[i];
				}
				m_options[k]->SetColor(EColor::White);
			}
		}
		lowTile->SetColor(EColor::White);
		/**
		}**/
		m_options[i]->SetColor(EColor::White);
	}
	return bestTile;
}


void ATile::PlayerChooseTile()
{
	this->m_color = EColor::Red;
	UMaterial* RedMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/MyContent/Materials/Red.Red'"));
	m_mesh->SetMaterial(0 ,RedMaterial);

}

void ATile::AIChooseTile()
{
	this->m_color = EColor::Blue;
	UMaterial* BlueMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/MyContent/Materials/Blue.Blue'"));
	m_mesh->SetMaterial(0, BlueMaterial);

}

bool ATile::Won(EColor color) const
{
	int FirstRow = 0;
	int SecondRow = 0;
	int ThirdRow = 0;
	int FirstColumn = 0;
	int SecondColumn = 0;
	int ThirdColumn = 0;
	int firstDiag = 0;
	int secondDiag = 0;
	for (int i = 0; i < 9; i++)
	{
		if (m_board[i]->GetColor() == color)
		{
			if (m_board[i]->m_x == 0)
			{
				FirstRow++;
			}
			if (m_board[i]->m_x == 1)
			{
				SecondRow++;
			}
			if (m_board[i]->m_x == 2)
			{
				ThirdRow++;
			}
			if (m_board[i]->m_y == 0)
			{
				FirstColumn++;
			}
			if (m_board[i]->m_y == 1)
			{
				SecondColumn++;
			}
			if (m_board[i]->m_y == 2)
			{
				ThirdColumn++;
			}
			if (m_board[i]->m_y == m_board[i]->m_x)
			{
				firstDiag++;
			}
			if (m_board[i]->m_y + m_board[i]->m_x == 2)
			{
				secondDiag++;
			}
		}
	}
	if (FirstColumn == 3 || SecondColumn == 3 || ThirdColumn == 3 || FirstRow == 3 || SecondRow == 3 || ThirdRow == 3 || firstDiag == 3 || secondDiag == 3)
	{
		return true;
	}
	return false;
}

int ATile::ScoreBoard() const
{
	int score = 0;
	/** Trying to classify 2 options to lose like a lose **/
	for (int i = 0; i < options_size; i++)
	{
		for (int j = 0; j < options_size; j++)
		{
			if (j != i)
			{
				m_options[i]->SetColor(EColor::Red);
				if (Won(EColor::Red))
				{
					m_options[i]->SetColor(EColor::White);
					m_options[j]->SetColor(EColor::Red);
					if (Won(EColor::Red))
					{
						score -= 100;
					}
					m_options[j]->SetColor(EColor::White);
				}
				m_options[i]->SetColor(EColor::White);
			}
		}
	}
	if (Won(EColor::Blue))
	{
		return 100;
	}
	if (Won(EColor::Red))
	{
		return -500;
	}
	for (int i = 0; i < 9; i++)
	{
		if (m_board[i]->m_x == 1 && m_board[i]->m_y == 1 && m_board[i]->GetColor() == EColor::Blue)
		{
			score += 3;
		}
		if (m_board[i]->m_x == 1 && m_board[i]->m_y == 1 && m_board[i]->GetColor() == EColor::Red)
		{
			score -= 3;
		}
		if (m_board[i]->m_x == 0 && m_board[i]->m_y == 0 && m_board[i]->GetColor() == EColor::Blue)
		{
			score += 1;
		}
		if (m_board[i]->m_x == 0 && m_board[i]->m_y == 0 && m_board[i]->GetColor() == EColor::Red)
		{
			score -= 1;
		}
		if (m_board[i]->m_x == 0 && m_board[i]->m_y == 2 && m_board[i]->GetColor() == EColor::Blue)
		{
			score += 1;
		}
		if (m_board[i]->m_x == 0 && m_board[i]->m_y == 2 && m_board[i]->GetColor() == EColor::Red)
		{
			score -= 1;
		}
		if (m_board[i]->m_x == 2 && m_board[i]->m_y == 0 && m_board[i]->GetColor() == EColor::Blue)
		{
			score += 1;
		}
		if (m_board[i]->m_x == 2 && m_board[i]->m_y == 0 && m_board[i]->GetColor() == EColor::Red)
		{
			score -= 1;
		}
		if (m_board[i]->m_x == 2 && m_board[i]->m_y == 2 && m_board[i]->GetColor() == EColor::Blue)
		{
			score += 1;
		}
		if (m_board[i]->m_x == 2 && m_board[i]->m_y == 2 && m_board[i]->GetColor() == EColor::Red)
		{
			score -= 1;
		}

	}

	return score;
}





