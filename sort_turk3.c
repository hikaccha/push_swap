/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_turk3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:56:00 by hichikaw          #+#    #+#             */
/*   Updated: 2025/06/01 21:06:48 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void	rotate_stack_a(t_stack *a, int pos_a, int size_a)
{
	if (pos_a <= size_a / 2)
	{
		while (pos_a-- > 0)
			ra(a);
	}
	else
	{
		pos_a = size_a - pos_a;
		while (pos_a-- > 0)
			rra(a);
	}
}

static void	rotate_stack_b(t_stack *b, int pos_b, int size_b)
{
	if (pos_b <= size_b / 2)
	{
		while (pos_b-- > 0)
			rb(b);
	}
	else
	{
		pos_b = size_b - pos_b;
		while (pos_b-- > 0)
			rrb(b);
	}
}

static void	execute_rotations_for_move(t_stack *a, t_stack *b,
	int pos_a, int pos_b)
{
	int	size_a;
	int	size_b;

	size_a = get_stack_size(a);
	size_b = get_stack_size(b);
	rotate_stack_a(a, pos_a, size_a);
	rotate_stack_b(b, pos_b, size_b);
}

static void	get_cheapest_element_b(t_stack *a, t_stack *b,
	int *cheapest_pos, int *value)
{
	t_node	*current;
	int		i;

	*cheapest_pos = find_cheapest_in_a(a, b);
	current = a->top;
	i = 0;
	while (i < *cheapest_pos && current)
	{
		current = current->next;
		i++;
	}
	*value = current->value;
}

void	move_cheapest_to_b(t_stack *a, t_stack *b)
{
	int	cheapest_pos;
	int	target_pos;
	int	value;

	get_cheapest_element_b(a, b, &cheapest_pos, &value);
	target_pos = find_position_in_b(b, value);
	execute_rotations_for_move(a, b, cheapest_pos, target_pos);
	pb(a, b);
}
