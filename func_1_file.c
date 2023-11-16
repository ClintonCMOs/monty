#include "monty.h"

void m_push(stack_t **stack, unsigned int line_number);
void m_pall(stack_t **stack, unsigned int line_number);
void m_pint(stack_t **stack, unsigned int line_number);
void m_pop(stack_t **stack, unsigned int line_number);
void m_swap(stack_t **stack, unsigned int line_number);

/**
 * m_push - Push to a stack_t linked list
 * @stack: A ptr to the top mode node of a stack_t linked list.
 * @line_number: The current working line number
 */
void m_push(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp, *new;
	int i;

	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		set_opcode_token_err(malloc_err());
		return;
	}

	if (op_toks[1] == NULL)
	{
		set_opcode_token_err(no_integer_err(line_number));
		return;
	}

	for (i = 0; op_toks[1][i]; i++)
	{
		if (op_toks[1][i] == '-' && i == 0)
			continue;
		if (op_toks[1][i] < '0' || op_toks[1][i] > '9')
		{
			set_opcode_token_err(no_integer_err(line_number));
			return;
		}
	}
	new->n = atoi(op_toks[1]);

	if (mode_checker(*stack) == STACK)
	{
		tmp = (*stack)->next;
		new->prev = *stack;
		new->next = tmp;
		if (tmp)
			tmp->prev = new;
		(*stack)->next = new;
	}
	else
	{
		tmp = *stack;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		new->next = NULL;
		tmp->next = new;
	}
}

/**
 * m_pall - Prints the values of a stack_t linked list.
 * @stack: A ptr to the top mode node of a stack_t linked list.
 * @line_number: The current working line number
 */
void m_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = (*stack)->next;

	while (tmp)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
	(void)line_number;
}

/**
 * m_pint - Prints the top value of a stack_t linked list.
 * @stack: A ptr to the top mode node of a stack_t linked list.
 * @line_number: The current working line number
 */
void m_pint(stack_t **stack, unsigned int line_number)
{
	if ((*stack)->next == NULL)
	{
		set_opcode_token_err(pint_err(line_number));
		return;
	}

	printf("%d\n", (*stack)->next->n);
}


/**
 * m_pop - Removes the top value element of a stack_t linked list.
 * @stack: A ptr to the top mode node of a stack_t linked list.
 * @line_number: The current working line number
 */
void m_pop(stack_t **stack, unsigned int line_number)
{
	stack_t *next = NULL;

	if ((*stack)->next == NULL)
	{
		set_opcode_token_err(pop_err(line_number));
		return;
	}

	next = (*stack)->next->next;
	free((*stack)->next);
	if (next)
		next->prev = *stack;
	(*stack)->next = next;
}

/**
 * m_swap - Swaps the top two value elements of a stack_t linked list.
 * @stack: A ptr to the top mode node of a stack_t linked list.
 * @line_number: The current working line number
 */
void m_swap(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		set_opcode_token_err(ss_error(line_number, "swap"));
		return;
	}

	tmp = (*stack)->next->next;
	(*stack)->next->next = tmp->next;
	(*stack)->next->prev = tmp;
	if (tmp->next)
		tmp->next->prev = (*stack)->next;
	tmp->next = (*stack)->next;
	tmp->prev = *stack;
	(*stack)->next = tmp;
}
