/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:00:00 by kato              #+#    #+#             */
/*   Updated: 2025/07/18 20:24:19 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min(t_stack *stack)
{
	t_node	*current;
	int		min;

	current = stack->top;
	min = current->value;
	while (current)
	{
		if (current->value < min)
			min = current->value;
		current = current->next;
	}
	return (min);
}

int	find_max(t_stack *stack)
{
	t_node	*current;
	int		max;

	current = stack->top;
	max = current->value;
	while (current)
	{
		if (current->value > max)
			max = current->value;
		current = current->next;
	}
	return (max);
}

void	assign_indexes(t_stack *stack)
{
	int		size;
	int		*arr;
	t_node	*cur;
	int		i;
	int		j;
	int		tmp;

	size = stack->size;
	arr = malloc(sizeof(int) * size);
	cur = stack->top;
	i = 0;
	if (!arr)
		error_exit(stack, NULL);
	while (cur)
	{
		arr[i++] = cur->value;
		cur = cur->next;
	}
	// バブルソート（小規模用）
	for (i = 0; i < size - 1; i++)
		for (j = 0; j < size - i - 1; j++)
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
	cur = stack->top;
	while (cur)
	{
		for (i = 0; i < size; i++)
			if (cur->value == arr[i])
			{
				cur->index = i;
				break ;
			}
		cur = cur->next;
	}
	free(arr);
}
