/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_turk5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:03:00 by hichikaw          #+#    #+#             */
/*   Updated: 2025/06/01 21:03:43 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void	final_rotation(t_stack *a, int min_pos)
{
	if (min_pos <= get_stack_size(a) / 2)
	{
		while (min_pos-- > 0)
			ra(a);
	}
	else
	{
		min_pos = get_stack_size(a) - min_pos;
		while (min_pos-- > 0)
			rra(a);
	}
}

void	turk_sort(t_stack *a, t_stack *b)
{
	int	min_pos;

	pb(a, b);
	pb(a, b);
	while (get_stack_size(a) > 3)
		move_cheapest_to_b(a, b);
	sort_three(a);
	while (b->top)
		move_cheapest_to_a(a, b);
	min_pos = get_position(a, get_min(a));
	final_rotation(a, min_pos);
}
