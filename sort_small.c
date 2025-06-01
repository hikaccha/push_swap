/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:20:24 by hichikaw          #+#    #+#             */
/*   Updated: 2025/06/01 20:31:43 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	sort_three(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	if (is_sorted(a))
		return ;
	if (get_stack_size(a) == 2)
	{
		if (a->top->value > a->top->next->value)
			sa(a);
		return ;
	}
	if (get_stack_size(a) < 3)
		return ;
		
	first = a->top->value;
	second = a->top->next->value;
	third = a->top->next->next->value;
	
	// 3つの要素のすべてのケースを明確に処理
	if (first < second && second < third)
		return ; // 既にソート済み
	else if (first > second && second < third && first < third)
		sa(a); // 2 1 3 -> 1 2 3
	else if (first < second && second > third && first < third)
	{
		sa(a); // 1 3 2 -> 3 1 2
		ra(a);  // 3 1 2 -> 1 2 3
	}
	else if (first > second && second > third && first > third)
	{
		sa(a);  // 3 2 1 -> 2 3 1
		rra(a); // 2 3 1 -> 1 2 3
	}
	else if (first > second && second < third && first > third)
		ra(a); // 3 1 2 -> 1 2 3
	else if (first < second && second > third && first > third)
		rra(a); // 2 3 1 -> 1 2 3
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
