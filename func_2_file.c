#include "monty.h"

void m_add(stack_t **stack, unsigned int line_number);
void m_sub(stack_t **stack, unsigned int line_number);
void m_div(stack_t **stack, unsigned int line_number);
void m_mul(stack_t **stack, unsigned int line_number);
void m_mod(stack_t **stack, unsigned int line_number);

/**
 * m_add - Adds the top two values of a stack_t linked list.
 * @stack: A ptr to the top mode node of a stack_t linked list.
 * @line_number: The current working line number
 */
void m_add(stack_t **stack, unsigned int line_number)
{
	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		set_opcode_token_err(ss_error(line_number, "add"));
		return;
	}

	(*stack)->next->next->n += (*stack)->next->n;
	m_pop(stack, line_number);
}

/**
 * m_sub - Subtracts the second value from the top of
 *             a stack_t linked list by the top value.
 * @stack: A ptr to the top mode node of a stack_t linked list.
 * @line_number: The current working line number
 */
void m_sub(stack_t **stack, unsigned int line_number)
{
	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		set_opcode_token_err(ss_error(line_number, "sub"));
		return;
	}

	(*stack)->next->next->n -= (*stack)->next->n;
	m_pop(stack, line_number);
}

/**
 * m_div - Divides the second value from the top of
 *             a stack_t linked list by the top value.
 * @stack: A ptr to the top mode node of a stack_t linked list.
 * @line_number: The current working line number
 */
void m_div(stack_t **stack, unsigned int line_number)
{
	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		set_opcode_token_err(ss_error(line_number, "div"));
		return;
	}

	if ((*stack)->next->n == 0)
	{
		set_opcode_token_err(div_err(line_number));
		return;
	}

	(*stack)->next->next->n /= (*stack)->next->n;
	m_pop(stack, line_number);
}

/**
 * m_mul - Multiplies the second value from the top of
 *             a stack_t linked list by the top value.
 * @stack: A ptr to the top mode node of a stack_t linked list.
 * @line_number: The current working line number
 */
void m_mul(stack_t **stack, unsigned int line_number)
{
	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		set_opcode_token_err(ss_error(line_number, "mul"));
		return;
	}

	(*stack)->next->next->n *= (*stack)->next->n;
	m_pop(stack, line_number);
}

/**
 * m_mod - Computes the modulus of the second value from the
 *             top of a stack_t linked list  by the top value.
 * @stack: A ptr to the top mode node of a stack_t linked list.
 * @line_number: The current working line number
 */
void m_mod(stack_t **stack, unsigned int line_number)
{
	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		set_opcode_token_err(ss_error(line_number, "mod"));
		return;
	}

	if ((*stack)->next->n == 0)
	{
		set_opcode_token_err(div_err(line_number));
		return;
	}

	(*stack)->next->next->n %= (*stack)->next->n;
	m_pop(stack, line_number);
}
