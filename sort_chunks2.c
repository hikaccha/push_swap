/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_chunks2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:47:00 by hichikaw          #+#    #+#             */
/*   Updated: 2025/06/01 20:47:11 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void	handle_chunk_element(t_stack *a, t_stack *b)
{
	pb(a, b);
	if (get_stack_size(b) > 1)
	{
		if (b->top->value < b->top->next->value)
			rb(b);
	}
}

void	move_chunk_to_b(t_stack *a, t_stack *b, int chunk_min, int chunk_max)
{
	int	size;
	int	rotations;

	size = get_stack_size(a);
	rotations = 0;
	while (rotations < size * 2)
	{
		if (a->top->value >= chunk_min && a->top->value <= chunk_max)
			handle_chunk_element(a, b);
		else
		{
			ra(a);
			rotations++;
		}
		if (!check_chunk_remaining(a, chunk_min, chunk_max))
			break ;
	}
}

void	move_max_to_a(t_stack *a, t_stack *b)
{
	int	b_max;
	int	b_max_pos;
	int	b_size;

	b_max = get_max(b);
	b_max_pos = get_position(b, b_max);
	b_size = get_stack_size(b);
	if (b_max_pos <= b_size / 2)
	{
		while (b->top->value != b_max)
			rb(b);
	}
	else
	{
		while (b->top->value != b_max)
			rrb(b);
	}
	pa(a, b);
}

int	check_chunk_remaining(t_stack *a, int chunk_min, int chunk_max)
{
	t_node	*current;

	current = a->top;
	while (current)
	{
		if (current->value >= chunk_min && current->value <= chunk_max)
			return (1);
		current = current->next;
	}
	return (0);
}
