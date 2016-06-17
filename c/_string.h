#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int my_strcmp(const char* str1, const char* str2)//×Ö·û´®±È½Ï
{
	assert(str1);
	assert(str2);

	while (*str1++ == *str2++)
	{
		if (*str1 == '\0')
			return 0;
	}
	if (*str1 > *str2)
		return 1;

	return 0;

}

char* my_strcopy( char* dst,const char* src)//×Ö·û´®¿½±´
{
	assert(dst);
	assert(src);

	char* ret = dst;

	while (*dst++ = *src++)
	{
		;
	}

	return ret;
}


char* my_strcat(char* dst, const char* src)
{
	assert(dst);
	assert(src);

	char* ret = dst;

	while (*dst)
	{
		*dst++;
	}

	while (*dst++ = *src++)
	{
		NULL;
	}
	return ret;
}

int my_strlen(const char* str)
{
	assert(str);
	int len = 0;

	while (*str++)
	{
		len++;
	}
	return len;
}

char* my_strstr( char* str,  char* sub_str)
{
	assert(str);
	assert(sub_str);

	for (int i = 0; str[i] != '\0'; i++)
	{
		int tmp = i;
		int j = 0;
		while (str[i++] == sub_str[j++])
		{
			if (sub_str[j] == '\0')
				return &str[tmp];
		}
		
		i = tmp;
	}
	return NULL;
}



