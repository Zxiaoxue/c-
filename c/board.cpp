#include "board.h"



//������
void PrintBoard(char board[ROW][COL])
{
	int i = 0;
	for (i = 0; i < ROW; i++)
	{
		cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << " " << endl;
		if (i != 2)
		{
			cout << "---|---|---";
		}
		printf("\n");
	}
}
void InitBoard(char board[ROW][COL])
{
	int i = 0;
	int j = 0;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void ShowMenu()
{
	printf("**************************************************************\n");
	printf("**************************************************************\n");
	printf("********************1.��Ϸ��ʼ********************************\n");
	printf("********************0.�˳���Ϸ********************************\n");
	printf("**************************************************************\n");
	printf("**************************************************************\n");
}

char EmptyBoard(char board[ROW][COL])
{
	int i = 0;
	int j = 0;
	for (i = 0; i < ROW; i++)
	{
		if (board[i][0] == board[i][1]
			&& board[i][1] == board[i][2]
			&& board[i][2] != ' ')
			return board[i][0];
	}
	for (i = 0; i < COL; i++)
	{
		if (board[0][i] == board[1][i]
			&& board[1][i] == board[2][i]
			&& board[0][1] != ' ')
			return board[0][i];
	}
	if (board[0][0] == board[1][1]
		&& board[1][1] == board[2][2]
		&& board[0][0] != ' ')
		return board[0][0];
	if (board[0][2] == board[1][1]
		&& board[1][1] == board[2][0]
		&& board[0][2] != ' ')
		return board[0][0];
	return ' ';
}

bool FullBoard(char board[ROW][COL])
{
	int i = 0;
	int j = 0;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (board[i][j] == ' ')
				return false;
		}
	}
	return true;
}

bool CheckBoard(char board[ROW][COL], int x, int y)
{
	return (board[x][y] == ' ')
		&& (x >= 0 && x < ROW)
		&& (y >= 0 && y < COL);

}

void ComputerMove(char board[ROW][COL])
{
	int i = 0;
	int j = 0;
	i = rand() % 3;
	j = rand() % 3;
	if (CheckBoard(board, i, j))
		board[i][j] = '$';
	else
	{
		ComputerMove(board);
	}

}

void PlayerMove(char board[ROW][COL])
{
	int i = 0;
	int j = 0;
	printf("����������:");
	scanf("%d %d", &i, &j);
	i--;
	j--;
	if (CheckBoard(board, i, j))
	{
		board[i][j] = '*';
	}
	else
	{
		printf("����������\n");
		PlayerMove(board);
	}

}

void Game(char board[ROW][COL])
{
	char ret = ' ';
	do
	{
		PlayerMove(board);
		PrintBoard(board);
		ret = EmptyBoard(board);

		if (FullBoard(board))
		{
			printf("ƽ�֣�\n");
			break;
		}
		if (ret == '*')
		{
			printf("���Ӯ��\n");
			break;
		}
		if (ret == '$')
		{
			printf("����Ӯ��\n");
			break;
		}
		ComputerMove(board);
		PrintBoard(board);
		ret = EmptyBoard(board);
		if (FullBoard(board))
		{
			printf("ƽ�֣�\n");
			break;
		}
		if (ret == '*')
		{
			printf("���Ӯ��\n");
			break;
		}
		if (ret == '$')
		{
			printf("����Ӯ��\n");
			break;
		}
	} while (ret == ' ');

}


void Test1()
{
	int input = 1;
	char board[ROW][COL] = { 0 };

	while (1)
	{
		InitBoard(board);
		ShowMenu();
		printf("��ѡ��\n");
		scanf("%d", &input);
		switch (input)
		{
		case BEGIN:
			Game(board);
			break;
		case EXIT:
			exit(1);//0�����˳���1�����˳�
			break;
		default:
			break;
		}
	}
}
