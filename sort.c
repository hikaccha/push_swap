/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:20:24 by hichikaw          #+#    #+#             */
/*   Updated: 2025/04/21 12:24:37 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	sort_chunks(t_stack *a, t_stack *b)
{
	int	chunk_count;
	int	chunk_size;
	int	chunk_number;
	int	chunk_min;
	int	chunk_max;
	int	min;
	int	size;

	size = get_stack_size(a);
	setup_chunks(a, size, &chunk_count, &chunk_size);
	min = get_min(a);
	chunk_number = 0;
	while (chunk_number < chunk_count)
	{
		chunk_min = min + chunk_number * chunk_size;
		chunk_max = chunk_min + chunk_size - 1;
		if (chunk_number == chunk_count - 1)
			chunk_max = get_max(a);
		move_chunk_to_b(a, b, chunk_min, chunk_max);
		chunk_number++;
	}
	while (b->top)
		move_max_to_a(a, b);
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
	else
		sort_chunks(a, b);
} 