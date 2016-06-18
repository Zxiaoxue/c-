#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int my_strncmp(const char* str1, const char* str2, int size)
{
	assert(str1);
	assert(str2);
	int i = size;

	while (*str1 == *str2 && i--)
	{
		if (*str2 == '\0')
		{
			return 0;
		}
	}
			
	if (*str1 > *str2)
		return 1;
	return -1;
}

char* my_strncopy(char* dst, const char* src, size_t size)//×Ö·û´®¿½±´
{
	assert(*dst);
	assert(*src);

	int i = size;
	char* ret = dst;

	while (i--)
	{
		*dst++ = *src++;
	}
	
	return ret;
}

char* my_strncat(char* dst, const char* src, size_t size)
{
	assert(dst);
	assert(src);
	char* ret = dst;
	size_t i = size;

	while (*dst)
	{
		*dst++;
	}
	while (i--)
	{
		*dst++ = *src++;
	}

	return ret;

}

