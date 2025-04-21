/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hichikaw <hichikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:20:24 by hichikaw          #+#    #+#             */
/*   Updated: 2025/04/21 12:30:13 by hichikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

int	is_integer(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	is_within_int_range(char *str)
{
	long long	num;
	int			sign;
	int			i;

	num = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && -num < INT_MIN))
			return (0);
		i++;
	}
	return (1);
}

int	has_duplicates(int *values, int count, int value)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (values[i] == value)
			return (1);
		i++;
	}
	return (0);
}

// 入力を昇順にスタックに積む処理
int	validate_input(int argc, char **argv, t_stack *stack)
{
	int	i;
	int	value;
	int	*values;
	int	count;

	if (argc == 1)
		return (0);
	count = argc - 1;
	values = (int *)malloc(sizeof(int) * count);
	if (!values)
		return (0);
	// 入力値を検証して配列に保存
	i = 0;
	while (i < count)
	{
		if (!is_integer(argv[i + 1]) || !is_within_int_range(argv[i + 1]))
		{
			free(values);
			return (0);
		}
		value = atoi(argv[i + 1]);
		if (has_duplicates(values, i, value))
		{
			free(values);
			return (0);
		}
		values[i] = value;
		i++;
	}
	// 逆順からスタックにプッシュ（配列の最後からプッシュすることで順序を保持）
	i = count - 1;
	while (i >= 0)
	{
		push(stack, values[i]);
		i--;
	}
	free(values);
	return (1);
} 