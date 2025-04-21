/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:20:24 by hichikaw          #+#    #+#             */
/*   Updated: 2025/04/21 13:24:37 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static void	cleanup_and_exit(t_stack *a, t_stack *b, int status)
{
	free_stack(a);
	free_stack(b);
	exit(status);
}

static void	handle_input_validation(t_stack *a, t_stack *b,
	int argc, char **argv)
{
	if (!validate_input(argc, argv, a))
	{
		printf("%s", error_message());
		cleanup_and_exit(a, b, 1);
	}
	if (is_sorted(a))
		cleanup_and_exit(a, b, 0);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	a = init_stack();
	b = init_stack();
	if (!a || !b)
	{
		printf("%s", error_message());
		if (a)
			free_stack(a);
		if (b)
			free_stack(b);
		return (1);
	}
	if (argc > 1)
	{
		handle_input_validation(a, b, argc, argv);
		sort_stack(a, b);
	}
	free_stack(a);
	free_stack(b);
	return (0);
}
