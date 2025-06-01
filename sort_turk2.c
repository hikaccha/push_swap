/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_turk2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:44:00 by hichikaw          #+#    #+#             */
/*   Updated: 2025/06/01 21:05:50 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

int	find_cheapest_in_a(t_stack *a, t_stack *b)
{
	int	size;
	int	cheapest_pos;
	int	cheapest_cost;
	int	current_cost;
	int	i;

	size = get_stack_size(a);
	cheapest_pos = 0;
	cheapest_cost = INT_MAX;
	i = 0;
	while (i < size)
	{
		current_cost = calculate_cost_a_to_b(a, b, i);
		if (current_cost < cheapest_cost)
		{
			cheapest_cost = current_cost;
			cheapest_pos = i;
		}
		i++;
	}
	return (cheapest_pos);
}

int	find_cheapest_in_b(t_stack *a, t_stack *b)
{
	int	size;
	int	cheapest_pos;
	int	cheapest_cost;
	int	current_cost;
	int	i;

	size = get_stack_size(b);
	cheapest_pos = 0;
	cheapest_cost = INT_MAX;
	i = 0;
	while (i < size)
	{
		current_cost = calculate_cost_b_to_a(a, b, i);
		if (current_cost < cheapest_cost)
		{
			cheapest_cost = current_cost;
			cheapest_pos = i;
		}
		i++;
	}
	return (cheapest_pos);
}
