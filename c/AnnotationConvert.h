#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

typedef enum State
{
	C_BEGIN,
	C_END,
}State;

void Convert(FILE* fIn, FILE*fOut)
{
	assert(fIn);
	assert(fOut);
	char first, second;
	State tag = C_END;
	do
	{
		first = fgetc(fIn);
		switch (first)
		{
			//1.普通情况 /*int i = 0;*/
		case'/':
			second = fgetc(fIn);
			if (second == '*')
			{
				//3.匹配问题
				if (tag == C_END)
				{
					fputc('/', fOut);
					fputc('/', fOut);
					tag = C_BEGIN;
				}
				else
				{
					fputc('/', fOut);
					fputc('*', fOut);
				}
			}
			//7.// /*xxxxxxxxxx*/
			else if (second == '/')
			{
				fputc('/', fOut);
				fputc('/', fOut);
				char next;
				do
				{
					next = fgetc(fIn);
					fputc(next, fOut);
				} while (next != '\n' && next != EOF);
			}
			else 
			{
				fputc(first, fOut);
				fputc(second, fOut);
			}
			break;
		case'*':
			second = fgetc(fIn);
			if (second == '/')
			{
				char next = fgetc(fIn);
				//5.多行注释  /**//**/
				fputc('\n', fOut);
				if (next == '/')
				{
					
					fseek(fIn, -1, SEEK_CUR);//倒退读取
				}
				//2.换行问题/*int i = 0;*/intj = 0;
				else if (next != '\n'&& next != EOF)
				{
					fputc(next, fOut);
				}
				else 
				{
					fputc('\n', fOut);
				}
				tag = C_END;
			}
			//6./***/
			else if (second == '*')
			{
				fputc(first, fOut);
				fseek(fIn, -1, SEEK_CUR);
			}
			else
			{
				fputc(first, fOut);
				fputc(second, fOut);
			}
			break;
		case'\n':
			//4.多行注释
			fputc('\n', fOut);
			if (tag == C_BEGIN)
			{
				fputc('/', fOut);
				fputc('/', fOut);
			}
			break;
		default:
			fputc(first, fOut);
			break;
		}
	}while (first != EOF);
}

void AnnotationConvert(const char* inputFile, const char* outputFile)
{
	FILE* fIn = fopen(inputFile, "r");
	if (fIn == NULL)
	{
		printf("打开文件%s失败，errno:%d", inputFile,errno);
		return;
	}
	FILE* fOut = fopen(outputFile, "w");
	if (fOut == NULL)
	{
		fclose(fIn);
		printf("打开文件%s失败，errno:%d", outputFile,errno);
		return;
	}
	Convert(fIn, fOut);

	fclose(fIn);
	fclose(fOut);

}


