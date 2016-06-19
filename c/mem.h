#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void* my_memcpy(void* dst, const void* src, size_t count)
{
	assert(dst);
	assert(src);

	char* ret = (char*)dst;
	char* _dst = ret;
	char* _src = (char*)src;

	while (--count)
	{
		*_dst++ = *_src++;
	}

	return dst;
}

void* my_memove(void* dst, const void* src, size_t count)
{
	assert(dst);
	assert(src);

	char* ret = (char*)dst;
	char* _dst = ret;
	char* _src = (char*)src;

	if ((_dst<_src) || (_dst>_src + count))
	{
		while (count--)
		{
			*_dst++ = *_src++;
		}
	}
	else
	{
		_dst = ret + count - 1;
		_src = _src + count - 1;
		
		while (count--)
		{
			*_dst-- = *_src--;
		}
	}
	return dst;
}


void* my_memset(void* ptr,int value,size_t num)
{
	assert(ptr);
	char* ret = (char*)ptr;

	while (num--)
	{
		*ret++ = (char)value;
	}
	
	return ptr;
}

int my_memcmp(const void* s1, const void* s2, size_t num)
{
	assert(s1);
	assert(s2);

	if (!num)
	{
		return 0;
	}

	char* _s1 = (char*)s1;
	char* _s2 = (char*)s2;

	while (num--&& *_s1 ==* _s2)
	{
		*_s1++ = *_s2++;
	}
	
	return (*_s1) - (*_s2);
}
