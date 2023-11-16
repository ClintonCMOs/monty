#include "monty.h"

/**
 * set_opcode_token_err - Sets last element of op_toks to be an error code.
 * @error_code: Int to store as a str in op_toks.
 */
void set_opcode_token_err(int error_code)
{
	int toks_len = 0, i = 0;
	char *exit_str = NULL;
	char **new_toks = NULL;

	toks_len = token_array_length();
	new_toks = malloc(sizeof(char *) * (toks_len + 2));
	if (!op_toks)
	{
		malloc_err();
		return;
	}
	while (i < toks_len)
	{
		new_toks[i] = op_toks[i];
		i++;
	}
	exit_str = get_integer(error_code);
	if (!exit_str)
	{
		free(new_toks);
		malloc_err();
		return;
	}
	new_toks[i++] = exit_str;
	new_toks[i] = NULL;
	free(op_toks);
	op_toks = new_toks;
}
