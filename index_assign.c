/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_assign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 10:00:00 by kato              #+#    #+#             */
/*   Updated: 2025/09/24 16:06:28 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	bubble_sort_values(int *arr, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	fill_values_from_stack(t_stack *stack, int *arr)
{
	int		i;
	t_node	*cur;

	i = 0;
	cur = stack->top;
	while (cur)
	{
		arr[i++] = cur->value;
		cur = cur->next;
	}
}

static void	assign_indices_from_sorted(t_stack *stack, int *arr, int size)
{
	t_node	*cur;
	int		i;

	cur = stack->top;
	while (cur)
	{
		i = 0;
		while (i < size)
		{
			if (cur->value == arr[i])
			{
				cur->index = i;
				break ;
			}
			i++;
		}
		cur = cur->next;
	}
}

void	assign_indexes(t_stack *stack)
{
	int		size;
	int		*arr;

	size = stack->size;
	arr = malloc(sizeof(int) * size);
	if (!arr)
		error_exit(stack, NULL);
	fill_values_from_stack(stack, arr);
	bubble_sort_values(arr, size);
	assign_indices_from_sorted(stack, arr, size);
	free(arr);
}
