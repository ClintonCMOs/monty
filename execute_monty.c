#include "monty.h"
#include <string.h>

void empty_tokens(void);
unsigned int token_array_length(void);
int is_empty_line(char *line, char *delimiters);
void (*get_op_func(char *opcode))(stack_t**, unsigned int);
int execute_monty(FILE *script_fd);

/**
 * empty_tokens - Empties global op_toks array of strings.
 */
void empty_tokens(void)
{
	size_t i = 0;

	if (op_toks == NULL)
		return;

	for (i = 0; op_toks[i]; i++)
		free(op_toks[i]);

	free(op_toks);
}

/**
 * token_array_length - Gets the length of current op_toks.
 *
 * Return: Length of current op_toks
 */
unsigned int token_array_length(void)
{
	unsigned int toks_len = 0;

	while (op_toks[toks_len])
		toks_len++;
	return (toks_len);
}

/**
 * is_empty_line - Checks if a line contains delimiters.
 * @line: A ptr to the line.
 * @delimiters: A str of delim chars
 *
 * Return: If the line only contains delimiters - 1.
 *         Otherwise - 0.
 */
int is_empty_line(char *line, char *delimiters)
{
	int i, j;

	for (i = 0; line[i]; i++)
	{
		for (j = 0; delimiters[j]; j++)
		{
			if (line[i] == delimiters[j])
				break;
		}
		if (delimiters[j] == '\0')
			return (0);
	}

	return (1);
}

/**
 * get_op_func - Matches an opcode
 * @opcode: The opcode to match.
 *
 * Return: A pointer to the function.
 */
void (*get_op_func(char *opcode))(stack_t**, unsigned int)
{
	instruction_t op_funcs[] = {
		{"push", m_push},
		{"pall", m_pall},
		{"pint", m_pint},
		{"pop", m_pop},
		{"swap", m_swap},
		{"add", m_add},
		{"nop", m_nop},
		{"sub", m_sub},
		{"div", m_div},
		{"mul", m_mul},
		{"mod", m_mod},
		{"pchar", m_putchar},
		{"pstr", m_pstr},
		{"rotl", m_rotl},
		{"rotr", m_rotr},
		{"stack", m_stack},
		{"queue", m_queue},
		{NULL, NULL}
	};
	int i;

	for (i = 0; op_funcs[i].opcode; i++)
	{
		if (strcmp(opcode, op_funcs[i].opcode) == 0)
			return (op_funcs[i].f);
	}

	return (NULL);
}

/**
 * execute_monty - function to execute a Monty script.
 * @script_fd: File descriptor for an open Monty bytecodes script.
 *
 * Return: EXIT_SUCCESS on success, respective error code on failure.
 */
int execute_monty(FILE *script_fd)
{
	stack_t *stack = NULL;
	char *line = NULL;
	size_t len = 0, exit_status = EXIT_SUCCESS;
	unsigned int line_number = 0, prev_tok_len = 0;
	void (*op_func)(stack_t**, unsigned int);

	if (initialize_stack(&stack) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	while (getline(&line, &len, script_fd) != -1)
	{
		line_number++;
		op_toks = str_tow(line, DELIMS);
		if (op_toks == NULL)
		{
			if (is_empty_line(line, DELIMS))
				continue;
			empty_stack(&stack);
			return (malloc_err());
		}
		else if (op_toks[0][0] == '#') /* comment line */
		{
			empty_tokens();
			continue;
		}
		op_func = get_op_func(op_toks[0]);
		if (op_func == NULL)
		{
			empty_stack(&stack);
			exit_status = op_unknown_err(op_toks[0], line_number);
			empty_tokens();
			break;
		}
		prev_tok_len = token_array_length();
		op_func(&stack, line_number);
		if (token_array_length() != prev_tok_len)
		{
			if (op_toks && op_toks[prev_tok_len])
				exit_status = atoi(op_toks[prev_tok_len]);
			else
				exit_status = EXIT_FAILURE;
			empty_tokens();
			break;
		}
		empty_tokens();
	}
	empty_stack(&stack);

	if (line && *line == 0)
	{
		free(line);
		return (malloc_err());
	}

	free(line);
	return (exit_status);
}
