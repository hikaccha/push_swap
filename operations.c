/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:20:24 by hichikaw          #+#    #+#             */
/*   Updated: 2025/04/21 12:26:29 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	sa(t_stack *a)
{
	swap(a);
	printf("sa\n");
}

void	sb(t_stack *b)
{
	swap(b);
	printf("sb\n");
}

void	pa(t_stack *a, t_stack *b)
{
	t_node	*temp;

	if (!b->top)
		return ;
	temp = b->top;
	b->top = b->top->next;
	temp->next = a->top;
	a->top = temp;
	printf("pa\n");
}

void	pb(t_stack *a, t_stack *b)
{
	t_node	*temp;

	if (!a->top)
		return ;
	temp = a->top;
	a->top = a->top->next;
	temp->next = b->top;
	b->top = temp;
	printf("pb\n");
}

void	ra(t_stack *a)
{
	rotate(a);
	printf("ra\n");
}

void	rb(t_stack *b)
{
	rotate(b);
	printf("rb\n");
}

void	rra(t_stack *a)
{
	reverse_rotate(a);
	printf("rra\n");
}

void	rrb(t_stack *b)
{
	reverse_rotate(b);
	printf("rrb\n");
}

void	ss(t_stack *a, t_stack *b)
{
	swap(a);
	swap(b);
	printf("ss\n");
}

void	rr(t_stack *a, t_stack *b)
{
	rotate(a);
	rotate(b);
	printf("rr\n");
}

void	rrr(t_stack *a, t_stack *b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	printf("rrr\n");
} 