#include <stdlib.h>

char **str_tow(char *str, char *delimiters);
int is_delim(char ch, char *delimiters);
int get_wordlen(char *str, char *delimiters);
int get_wordlcount(char *str, char *delimiters);
char *get_nxtword(char *str, char *delimiters);

/**
 * str_tow - takes a string and seperates its words
 *
 * @str: str to seperate into words
 * @delimiters: delim to use to delimit words
 *
 * Return: 2D array of pointers to each word
 */

char **str_tow(char *str, char *delimiters)
{
	char **words = NULL;
	int wc, wordLen, n, i = 0;

	if (str == NULL || !*str)
		return (NULL);
	wc = get_wordlcount(str, delimiters);


	if (wc == 0)
		return (NULL);
	words = malloc((wc + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	while (i < wc)
	{
		wordLen = get_wordlen(str, delimiters);
		if (is_delim(*str, delimiters))
		{
			str = get_nxtword(str, delimiters);
		}
		words[i] = malloc((wordLen + 1) * sizeof(char));
		if (words[i] == NULL)
		{
			while (i >= 0)
			{
				i--;
				free(words[i]);
			}
			free(words);
			return (NULL);
		}
		n = 0;
		while (n < wordLen)
		{
			words[i][n] = *(str + n);
			n++;
		}
		words[i][n] = '\0';
		str = get_nxtword(str, delimiters);
		i++;
	}
	words[i] = NULL;
	return (words);
}

/**
 * is_delim - checks if stream has delimitor char
 *
 * @ch: char in stream
 *
 * @delimiters: Ptr to null terminated array of delimitors
 *
 * Return: 1 if success, 0 if fail
 */

int is_delim(char ch, char *delimiters)
{
	int i = 0;

	while (delimiters[i])
	{
		if (delimiters[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

/**
 * get_wordlen - gets the word length of cur word in str
 *
 * @str: str to get word length from current word
 * @delimiters: delim to use to delimit words
 *
 * Return: word lenof current word
 */

int get_wordlen(char *str, char *delimiters)
{
	int wLen = 0, awaiting = 1, i = 0;

	while (*(str + i))
	{
		if (is_delim(str[i], delimiters))
			awaiting = 1;
		else if (awaiting)
		{
			wLen++;
		}
		if (wLen > 0 && is_delim(str[i], delimiters))
			break;
		i++;
	}
	return (wLen);
}

/**
 * get_wordlcount - gets the word count of a string
 *
 * @str: str to get word count from
 * @delimiters: delim to use to delimit words
 *
 * Return: the word count of the string
 */

int get_wordlcount(char *str, char *delimiters)
{
	int wc = 0, awaiting = 1, i = 0;

	while (*(str + i))
	{
		if (is_delim(str[i], delimiters))
			awaiting = 1;
		else if (awaiting)
		{
			awaiting = 0;
			wc++;
		}
		i++;
	}
	return (wc);
}

/**
 * get_nxtword - gets the next word in a string
 *
 * @str: str to get next word from
 * @delimiters: delim to use to delimit words
 *
 * Return: ptr to first char of next word
 */

char *get_nxtword(char *str, char *delimiters)
{
	int awaiting = 0;
	int i = 0;

	while (*(str + i))
	{
		if (is_delim(str[i], delimiters))
			awaiting = 1;
		else if (awaiting)
			break;
		i++;
	}
	return (str + i);
}
