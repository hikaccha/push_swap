/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:20:24 by hichikaw          #+#    #+#             */
/*   Updated: 2025/06/01 20:34:03 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

// 指定位置まで回転（単一スタック用）
static void	rotate_to_position(t_stack *stack, int pos, int is_stack_a)
{
	int	size;
	int	i;

	size = get_stack_size(stack);
	if (pos <= size / 2)
	{
		for (i = 0; i < pos; i++)
		{
			if (is_stack_a)
				ra(stack);
			else
				rb(stack);
		}
	}
	else
	{
		for (i = 0; i < size - pos; i++)
		{
			if (is_stack_a)
				rra(stack);
			else
				rrb(stack);
		}
	}
}

// Turk Algorithmの実装: 最初に2つの要素をスタックBに移動
static void	push_first_two(t_stack *a, t_stack *b)
{
	pb(a, b);
	pb(a, b);
}

// スタックBでの正しい位置を見つける（修正版）
static int	find_position_in_b(t_stack *b, int value)
{
	t_node	*current;
	int		pos;
	int		max_value;
	int		min_value;

	if (!b->top)
		return (0);

	max_value = get_max(b);
	min_value = get_min(b);
	
	// 新しい最大値の場合
	if (value > max_value)
		return (get_position(b, max_value));
	
	// 新しい最小値の場合
	if (value < min_value)
		return (get_position(b, max_value));

	// 適切な位置を探す
	current = b->top;
	pos = 0;
	while (current)
	{
		t_node *next = current->next;
		if (!next)
			next = b->top; // 循環リストとして扱う
		
		if ((current->value > value && next->value < value) ||
			(current->value > value && next->value > current->value))
			return ((pos + 1) % get_stack_size(b));
		
		current = current->next;
		pos++;
		if (current == b->top) // 循環完了
			break;
	}

	return (0);
}

// スタックAでの正しい位置を見つける
static int	find_position_in_a(t_stack *a, int value)
{
	t_node	*current;
	int		pos;
	int		target_value;
	int		target_pos;

	current = a->top;
	pos = 0;
	target_value = INT_MAX;
	target_pos = 0;

	while (current)
	{
		if (current->value > value && current->value < target_value)
		{
			target_value = current->value;
			target_pos = pos;
		}
		current = current->next;
		pos++;
	}

	// 適切な位置が見つからない場合は最小値の位置
	if (target_value == INT_MAX)
		return (get_position(a, get_min(a)));

	return (target_pos);
}

// 回転コストを計算
static int	calculate_rotation_cost(int pos, int size)
{
	if (pos <= size / 2)
		return (pos);
	else
		return (size - pos);
}

// スタックAからスタックBへの移動コストを計算
static int	calculate_cost_a_to_b(t_stack *a, t_stack *b, int pos_a)
{
	t_node	*current;
	int		value;
	int		pos_b;
	int		cost_a;
	int		cost_b;
	int		i;

	current = a->top;
	i = 0;
	while (i < pos_a && current)
	{
		current = current->next;
		i++;
	}
	if (!current)
		return (INT_MAX);

	value = current->value;
	pos_b = find_position_in_b(b, value);
	cost_a = calculate_rotation_cost(pos_a, get_stack_size(a));
	cost_b = calculate_rotation_cost(pos_b, get_stack_size(b));

	return (cost_a + cost_b);
}

// スタックBからスタックAへの移動コストを計算
static int	calculate_cost_b_to_a(t_stack *a, t_stack *b, int pos_b)
{
	t_node	*current;
	int		value;
	int		pos_a;
	int		cost_a;
	int		cost_b;
	int		i;

	current = b->top;
	i = 0;
	while (i < pos_b && current)
	{
		current = current->next;
		i++;
	}
	if (!current)
		return (INT_MAX);

	value = current->value;
	pos_a = find_position_in_a(a, value);
	cost_a = calculate_rotation_cost(pos_a, get_stack_size(a));
	cost_b = calculate_rotation_cost(pos_b, get_stack_size(b));

	return (cost_a + cost_b);
}

// 最小コストの要素を見つける
static int	find_cheapest_in_a(t_stack *a, t_stack *b)
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

static int	find_cheapest_in_b(t_stack *a, t_stack *b)
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

// 最適化された回転実行
static void	execute_rotations(t_stack *a, t_stack *b, int pos_a, int pos_b)
{
	int	size_a = get_stack_size(a);
	int	size_b = get_stack_size(b);
	int	moves_a = (pos_a <= size_a / 2) ? pos_a : size_a - pos_a;
	int	moves_b = (pos_b <= size_b / 2) ? pos_b : size_b - pos_b;
	int	rotate_a = (pos_a <= size_a / 2);
	int	rotate_b = (pos_b <= size_b / 2);
	int	i;

	// 同じ方向の回転を最適化
	if (rotate_a && rotate_b)
	{
		int common_moves = (moves_a < moves_b) ? moves_a : moves_b;
		for (i = 0; i < common_moves; i++)
			rr(a, b);
		moves_a -= common_moves;
		moves_b -= common_moves;
	}
	else if (!rotate_a && !rotate_b)
	{
		int common_moves = (moves_a < moves_b) ? moves_a : moves_b;
		for (i = 0; i < common_moves; i++)
			rrr(a, b);
		moves_a -= common_moves;
		moves_b -= common_moves;
	}

	// 残りの回転を実行
	for (i = 0; i < moves_a; i++)
	{
		if (rotate_a)
			ra(a);
		else
			rra(a);
	}

	for (i = 0; i < moves_b; i++)
	{
		if (rotate_b)
			rb(b);
		else
			rrb(b);
	}
}

// 最小コストでスタックAからスタックBに移動（最適化版）
static void	move_cheapest_to_b(t_stack *a, t_stack *b)
{
	int	cheapest_pos;
	int	target_pos;
	t_node	*current;
	int	value;
	int	i;

	cheapest_pos = find_cheapest_in_a(a, b);
	
	current = a->top;
	i = 0;
	while (i < cheapest_pos && current)
	{
		current = current->next;
		i++;
	}
	value = current->value;
	target_pos = find_position_in_b(b, value);

	execute_rotations(a, b, cheapest_pos, target_pos);
	pb(a, b);
}

// 最小コストでスタックBからスタックAに移動（最適化版）
static void	move_cheapest_to_a(t_stack *a, t_stack *b)
{
	int	cheapest_pos;
	int	target_pos;
	t_node	*current;
	int	value;
	int	i;

	cheapest_pos = find_cheapest_in_b(a, b);
	
	current = b->top;
	i = 0;
	while (i < cheapest_pos && current)
	{
		current = current->next;
		i++;
	}
	value = current->value;
	target_pos = find_position_in_a(a, value);

	execute_rotations(a, b, target_pos, cheapest_pos);
	pa(a, b);
}

// Turk Algorithm: メインのソート関数
static void	turk_sort(t_stack *a, t_stack *b)
{
	// ステップ1: 最初の2つをスタックBに移動
	push_first_two(a, b);

	// ステップ2: 残りを最小コストでスタックBに移動（3つ残すまで）
	while (get_stack_size(a) > 3)
		move_cheapest_to_b(a, b);

	// ステップ3: 残り3つをソート
	sort_three(a);

	// ステップ4: スタックBから最小コストでスタックAに戻す
	while (b->top)
		move_cheapest_to_a(a, b);

	// ステップ5: 最小値を先頭に移動
	int min_pos = get_position(a, get_min(a));
	rotate_to_position(a, min_pos, 1);
}

void	sort_chunks(t_stack *a, t_stack *b)
{
	turk_sort(a, b);
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
	{
		// 中サイズは簡単なアプローチ
		while (get_stack_size(a) > 3)
			pb(a, b);
		sort_three(a);
		while (b->top)
		{
			int max_pos = get_position(b, get_max(b));
			rotate_to_position(b, max_pos, 0);
			pa(a, b);
		}
		int min_pos = get_position(a, get_min(a));
		rotate_to_position(a, min_pos, 1);
	}
	else
		turk_sort(a, b);
}
