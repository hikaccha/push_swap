/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:20:24 by hichikaw          #+#    #+#             */
/*   Updated: 2025/04/21 12:28:20 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

char	*error_message(void)
{
	char	*error_message;

	error_message = "Error\n";
	return (error_message);
}

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack || !stack->top)
		return (1);
	current = stack->top;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

int	get_min(t_stack *stack)
{
	t_node	*current;
	int		min;

	if (!stack || !stack->top)
		return (INT_MAX);
	min = stack->top->value;
	current = stack->top->next;
	while (current)
	{
		if (current->value < min)
			min = current->value;
		current = current->next;
	}
	return (min);
}

int	get_max(t_stack *stack)
{
	t_node	*current;
	int		max;

	if (!stack || !stack->top)
		return (INT_MIN);
	max = stack->top->value;
	current = stack->top->next;
	while (current)
	{
		if (current->value > max)
			max = current->value;
		current = current->next;
	}
	return (max);
}

int	get_stack_size(t_stack *stack)
{
	t_node	*current;
	int		size;

	if (!stack || !stack->top)
		return (0);
	size = 0;
	current = stack->top;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

int	get_position(t_stack *stack, int value)
{
	t_node	*current;
	int		position;

	if (!stack || !stack->top)
		return (-1);
	position = 0;
	current = stack->top;
	while (current)
	{
		if (current->value == value)
			return (position);
		position++;
		current = current->next;
	}
	return (-1);
} 