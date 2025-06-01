/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:20:24 by hichikaw          #+#    #+#             */
/*   Updated: 2025/06/01 20:54:55 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void	rotate_forward(t_stack *stack, int pos, int is_stack_a)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		if (is_stack_a)
			ra(stack);
		else
			rb(stack);
		i++;
	}
}

static void	rotate_backward(t_stack *stack, int moves, int is_stack_a)
{
	int	i;

	i = 0;
	while (i < moves)
	{
		if (is_stack_a)
			rra(stack);
		else
			rrb(stack);
		i++;
	}
}

static void	rotate_to_position(t_stack *stack, int pos, int is_stack_a)
{
	int	size;

	size = get_stack_size(stack);
	if (pos <= size / 2)
		rotate_forward(stack, pos, is_stack_a);
	else
		rotate_backward(stack, size - pos, is_stack_a);
}

static void	simple_sort_medium(t_stack *a, t_stack *b)
{
	int	max_pos;
	int	min_pos;

	while (get_stack_size(a) > 3)
		pb(a, b);
	sort_three(a);
	while (b->top)
	{
		max_pos = get_position(b, get_max(b));
		rotate_to_position(b, max_pos, 0);
		pa(a, b);
	}
	min_pos = get_position(a, get_min(a));
	rotate_to_position(a, min_pos, 1);
}

void	sort_stack(t_stack *a, t_stack *b)
{
	int	size;

	size = get_stack_size(a);
	if (is_sorted(a) || size <= 1)
		return ;
	if (size <= 3)
		sort_three(a);
	else if (size <= 5)
		sort_five(a, b);
	else if (size <= 20)
		simple_sort_medium(a, b);
	else
		turk_sort(a, b);
}
