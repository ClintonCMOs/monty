#include "monty.h"

void m_nop(stack_t **stack, unsigned int line_number);
void m_putchar(stack_t **stack, unsigned int line_number);
void m_pstr(stack_t **stack, unsigned int line_number);

/**
 * m_nop - Does absolutely nothing for the Monty opcode 'nop'.
 * @stack: A ptrto the top mode node of a stack_t linked list.
 * @line_number: The current working line number
 */
void m_nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

/**
 * m_putchar - Prints the character in the top value
 *               node of a stack_t linked list.
 * @stack: A ptr to the top mode node of a stack_t linked list.
 * @line_number: The current working line number
 */
void m_putchar(stack_t **stack, unsigned int line_number)
{
	if ((*stack)->next == NULL)
	{
		set_opcode_token_err(putchar_error(line_number, "stack empty"));
		return;
	}
	if ((*stack)->next->n < 0 || (*stack)->next->n > 127)
	{
		set_opcode_token_err(putchar_error(line_number,
					     "value out of range"));
		return;
	}

	printf("%c\n", (*stack)->next->n);
}

/**
 * m_pstr - Prints the string contained in a stack_t linked list.
 * @stack: A ptr to the top mode node of a stack_t linked list.
 * @line_number: The current working line number
 */
void m_pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = (*stack)->next;

	while (tmp && tmp->n != 0 && (tmp->n > 0 && tmp->n <= 127))
	{
		printf("%c", tmp->n);
		tmp = tmp->next;
	}

	printf("\n");

	(void)line_number;
}
