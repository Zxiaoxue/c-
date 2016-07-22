#include "board.h"



//三子棋
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
	printf("********************1.游戏开始********************************\n");
	printf("********************0.退出游戏********************************\n");
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
	printf("请输入坐标:");
	scanf("%d %d", &i, &j);
	i--;
	j--;
	if (CheckBoard(board, i, j))
	{
		board[i][j] = '*';
	}
	else
	{
		printf("请重新输入\n");
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
			printf("平局！\n");
			break;
		}
		if (ret == '*')
		{
			printf("玩家赢！\n");
			break;
		}
		if (ret == '$')
		{
			printf("电脑赢！\n");
			break;
		}
		ComputerMove(board);
		PrintBoard(board);
		ret = EmptyBoard(board);
		if (FullBoard(board))
		{
			printf("平局！\n");
			break;
		}
		if (ret == '*')
		{
			printf("玩家赢！\n");
			break;
		}
		if (ret == '$')
		{
			printf("电脑赢！\n");
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
		printf("请选择：\n");
		scanf("%d", &input);
		switch (input)
		{
		case BEGIN:
			Game(board);
			break;
		case EXIT:
			exit(1);//0错误退出，1正常退出
			break;
		default:
			break;
		}
	}
}
