/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_chunks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:20:24 by hichikaw          #+#    #+#             */
/*   Updated: 2025/06/01 20:50:11 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	setup_chunks(t_stack *a, int size, int *chunk_count, int *chunk_size)
{
	int	min;
	int	max;

	if (size <= 100)
		*chunk_count = 5;
	else
		*chunk_count = 11;
	min = get_min(a);
	max = get_max(a);
	*chunk_size = (max - min + 1) / *chunk_count;
}

static void	process_all_chunks(t_stack *a, t_stack *b, int min, int info[2])
{
	int	chunk_number;
	int	chunk_min;
	int	chunk_max;

	chunk_number = 0;
	while (chunk_number < info[0])
	{
		chunk_min = min + chunk_number * info[1];
		chunk_max = chunk_min + info[1] - 1;
		if (chunk_number == info[0] - 1)
			chunk_max = get_max(a);
		move_chunk_to_b(a, b, chunk_min, chunk_max);
		chunk_number++;
	}
}

void	sort_chunks(t_stack *a, t_stack *b)
{
	int	chunk_info[2];
	int	min;
	int	size;

	size = get_stack_size(a);
	setup_chunks(a, size, &chunk_info[0], &chunk_info[1]);
	min = get_min(a);
	process_all_chunks(a, b, min, chunk_info);
	while (b->top)
		move_max_to_a(a, b);
}
