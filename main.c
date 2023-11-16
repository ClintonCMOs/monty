#include "monty.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char **op_toks = NULL;

/**
 * main - the entry point for the program
 *
 * @argc: arg count
 * @argv: arg ptr
 *
 * Return: (EXIT_SUCCESS) on success (EXIT_FAILURE) on error
 */
int main(int argc, char **argv)
{
	FILE *script_fd = NULL;
	int exit_code = EXIT_SUCCESS;

	if (argc != 2)
		return (use_err());
	script_fd = fopen(argv[1], "r");
	if (script_fd == NULL)
		return (file_err_open(argv[1]));
	exit_code = execute_monty(script_fd);
	fclose(script_fd);
	return (exit_code);
}
