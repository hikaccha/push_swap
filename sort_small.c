/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:20:24 by hichikaw          #+#    #+#             */
/*   Updated: 2025/04/21 14:28:25 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void	handle_three_cases(t_stack *a, int first, int second, int third)
{
	if (first > second && first < third)
		sa(a);
	else if (first > second && second < third && first > third)
	{
		sa(a);
		rra(a);
	}
	else if (first > second && second > third)
	{
		sa(a);
		rra(a);
		sa(a);
	}
	else if (first < second && second > third && first < third)
	{
		sa(a);
		ra(a);
	}
	else if (first < second && second > third && first > third)
		rra(a);
}

void	sort_three(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	if (is_sorted(a))
		return ;
	if (get_stack_size(a) == 2)
	{
		sa(a);
		return ;
	}
	first = a->top->value;
	second = a->top->next->value;
	third = a->top->next->next->value;
	handle_three_cases(a, first, second, third);
}

void	move_min_to_b(t_stack *a, t_stack *b, int *size)
{
	int	min;
	int	min_pos;

	min = get_min(a);
	min_pos = get_position(a, min);
	if (min_pos <= *size / 2)
	{
		while (a->top->value != min)
			ra(a);
	}
	else
	{
		while (a->top->value != min)
			rra(a);
	}
	pb(a, b);
	(*size)--;
}

void	sort_five(t_stack *a, t_stack *b)
{
	int	size;

	if (is_sorted(a))
		return ;
	size = get_stack_size(a);
	while (size > 3 && !is_sorted(a))
		move_min_to_b(a, b, &size);
	sort_three(a);
	while (b->top)
		pa(a, b);
}
