/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_chunks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:20:24 by hichikaw          #+#    #+#             */
/*   Updated: 2025/06/01 20:24:53 by hichikaw         ###   ########.fr       */
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

void	move_chunk_to_b(t_stack *a, t_stack *b, int chunk_min, int chunk_max)
{
	int	size;
	int	rotations;

	size = get_stack_size(a);
	rotations = 0;
	
	while (rotations < size * 2) // 無限ループ防止
	{
		if (a->top->value >= chunk_min && a->top->value <= chunk_max)
		{
			pb(a, b);
			// より効率的な配置: 大きい値は上に保持
			if (get_stack_size(b) > 1 && b->top->value < b->top->next->value)
				rb(b);
		}
		else
		{
			ra(a);
			rotations++;
		}
		
		// チャンク内の要素がすべて移動されたかチェック
		t_node *current = a->top;
		int found = 0;
		while (current)
		{
			if (current->value >= chunk_min && current->value <= chunk_max)
			{
				found = 1;
				break;
			}
			current = current->next;
		}
		if (!found)
			break;
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
