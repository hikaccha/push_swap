/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:20:24 by hichikaw          #+#    #+#             */
/*   Updated: 2025/06/01 20:56:11 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_node
{
	int				value;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
}	t_stack;

/* スタック基本操作 */
t_stack	*init_stack(void);
void	push(t_stack *stack, int value);
int		pop(t_stack *stack);
void	swap(t_stack *stack);
void	rotate(t_stack *stack);
void	reverse_rotate(t_stack *stack);
void	free_stack(t_stack *stack);

/* push_swap命令セット */
void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);

/* ユーティリティ関数 */
char	*error_message(void);
int		is_sorted(t_stack *stack);
int		get_min(t_stack *stack);
int		get_max(t_stack *stack);
int		get_stack_size(t_stack *stack);
int		get_position(t_stack *stack, int value);

/* 入力検証関数 */
int		is_integer(char *str);
int		is_within_int_range(char *str);
int		has_duplicates(int *values, int count, int value);
int		validate_input(int argc, char **argv, t_stack *stack);

/* ソート関数 */
void	sort_three(t_stack *a);
void	sort_five(t_stack *a, t_stack *b);
void	setup_chunks(t_stack *a, int size, int *chunk_count, int *chunk_size);
void	move_chunk_to_b(t_stack *a, t_stack *b, int chunk_min, int chunk_max);
void	move_max_to_a(t_stack *a, t_stack *b);
void	sort_chunks(t_stack *a, t_stack *b);
void	sort_stack(t_stack *a, t_stack *b);

/* Turk Algorithm関数 */
int		find_cheapest_in_a(t_stack *a, t_stack *b);
int		find_cheapest_in_b(t_stack *a, t_stack *b);
int		calculate_cost_a_to_b(t_stack *a, t_stack *b, int pos_a);
int		calculate_cost_b_to_a(t_stack *a, t_stack *b, int pos_b);
int		check_chunk_remaining(t_stack *a, int chunk_min, int chunk_max);
void	move_cheapest_to_b(t_stack *a, t_stack *b);
void	move_cheapest_to_a(t_stack *a, t_stack *b);
int		find_position_in_b(t_stack *b, int value);
int		find_position_in_a(t_stack *a, int value);
void	turk_sort(t_stack *a, t_stack *b);

#endif
