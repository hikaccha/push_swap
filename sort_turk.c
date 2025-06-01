/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_turk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:35:00 by hichikaw          #+#    #+#             */
/*   Updated: 2025/06/01 20:54:02 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

int	find_position_in_b(t_stack *b, int value)
{
	t_node	*current;
	int		pos;
	int		max_value;
	int		min_value;

	if (!b->top)
		return (0);
	max_value = get_max(b);
	min_value = get_min(b);
	if (value > max_value)
		return (get_position(b, max_value));
	if (value < min_value)
		return (get_position(b, max_value));
	current = b->top;
	pos = 0;
	while (current)
	{
		if (current->next && current->value > value
			&& current->next->value < value)
			return (pos + 1);
		current = current->next;
		pos++;
	}
	return (0);
}

int	find_position_in_a(t_stack *a, int value)
{
	t_node	*current;
	int		pos;
	int		target_value;
	int		target_pos;

	current = a->top;
	pos = 0;
	target_value = INT_MAX;
	target_pos = 0;
	while (current)
	{
		if (current->value > value && current->value < target_value)
		{
			target_value = current->value;
			target_pos = pos;
		}
		current = current->next;
		pos++;
	}
	if (target_value == INT_MAX)
		return (get_position(a, get_min(a)));
	return (target_pos);
}

static int	calculate_rotation_cost(int pos, int size)
{
	if (pos <= size / 2)
		return (pos);
	else
		return (size - pos);
}

int	calculate_cost_a_to_b(t_stack *a, t_stack *b, int pos_a)
{
	t_node	*current;
	int		value;
	int		pos_b;
	int		cost_a;
	int		i;

	current = a->top;
	i = 0;
	while (i < pos_a && current)
	{
		current = current->next;
		i++;
	}
	if (!current)
		return (INT_MAX);
	value = current->value;
	pos_b = find_position_in_b(b, value);
	cost_a = calculate_rotation_cost(pos_a, get_stack_size(a));
	return (cost_a + calculate_rotation_cost(pos_b, get_stack_size(b)));
}

int	calculate_cost_b_to_a(t_stack *a, t_stack *b, int pos_b)
{
	t_node	*current;
	int		value;
	int		pos_a;
	int		cost_b;
	int		i;

	current = b->top;
	i = 0;
	while (i < pos_b && current)
	{
		current = current->next;
		i++;
	}
	if (!current)
		return (INT_MAX);
	value = current->value;
	pos_a = find_position_in_a(a, value);
	cost_b = calculate_rotation_cost(pos_b, get_stack_size(b));
	return (cost_b + calculate_rotation_cost(pos_a, get_stack_size(a)));
}
