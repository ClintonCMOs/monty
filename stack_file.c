#include "monty.h"
#include <string.h>

void empty_stack(stack_t **stack);
int initialize_stack(stack_t **stack);
int mode_checker(stack_t *stack);

/**
 * empty_stack - Frees a stack_t stack.
 * @stack: A ptr to the top (stack) or
 *         bottom (queue) of a stack_t.
 */
void empty_stack(stack_t **stack)
{
	stack_t *tmp = *stack;

	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}

/**
 * initialize_stack - Initializes a stack_t stack with beginning
 *              stack and ending queue nodes.
 * @stack: A ptr to an unitialized stack_t stack.
 *
 * Return: If an error occurs - EXIT_FAILURE.
 *         Otherwise - EXIT_SUCCESS.
 */
int initialize_stack(stack_t **stack)
{
	stack_t *s;

	s = malloc(sizeof(stack_t));
	if (s == NULL)
		return (malloc_err());

	s->n = STACK;
	s->prev = NULL;
	s->next = NULL;

	*stack = s;

	return (EXIT_SUCCESS);
}

/**
 * mode_checker - Checks if a stack_t linked list is in stack or queue mode.
 * @stack: A ptr to the top (stack) or bottom (queue)
 *         of a stack_t linked list.
 *
 * Return: If the stack_t is in stack mode - STACK (0).
 *         If the stack_t is in queue mode - QUEUE (1).
 *         Otherwise - 2.
 */
int mode_checker(stack_t *stack)
{
	if (stack->n == STACK)
		return (STACK);
	else if (stack->n == QUEUE)
		return (QUEUE);
	return (2);
}
