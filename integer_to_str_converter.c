#include <stdlib.h>

char *get_integer(int num);
unsigned int _abs(int);
int extract_numbase_length(unsigned int num, unsigned int base);
void populate_numbase_buffer(unsigned int num, unsigned int base,
		       char *buff, int buff_size);

/**
 * get_integer - gets a char ptr to new str with int
 * @num: num to convert
 *
 * Return: char ptr to str. NULL if malloc fails
 */
char *get_integer(int num)
{
	unsigned int temp;
	int length = 0;
	long num_l = 0;
	char *ret;

	temp = _abs(num);
	length = extract_numbase_length(temp, 10);

	if (num < 0 || num_l < 0)
		length++; 
	ret = malloc(length + 1);
	if (!ret)
		return (NULL);

	populate_numbase_buffer(temp, 10, ret, length);
	if (num < 0 || num_l < 0)
		ret[0] = '-';

	return (ret);
}

/**
 * _abs - absolute value of an int
 * @i: int
 *
 * Return: unsigned integer
 */
unsigned int _abs(int i)
{
	if (i < 0)
		return (-(unsigned int)i);
	return ((unsigned int)i);
}

/**
 * extract_numbase_length - get length of buffer
 * @num: number to get length needed for
 * @base: number base
 *
 * Return: int
 */
int extract_numbase_length(unsigned int num, unsigned int base)
{
	int len = 1;

	while (num > base - 1)
	{
		len++;
		num /= base;
	}
	return (len);
}

/**
 * populate_numbase_buffer - fills buffer with correct numbers up to base 36
 * @num: number to convert
 * @base: base of number used
 * @buff: buffer to fill with result of conversion
 * @buff_size: buffer size in bytes
 *
 * Return: always void.
 */
void populate_numbase_buffer(unsigned int num, unsigned int base,
			char *buff, int buff_size)
{
	int rem, i = buff_size - 1;

	buff[buff_size] = '\0';
	while (i >= 0)
	{
		rem = num % base;
		if (rem > 9)
			buff[i] = rem + 87;
		else
			buff[i] = rem + '0';
		num /= base;
		i--;
	}
}
