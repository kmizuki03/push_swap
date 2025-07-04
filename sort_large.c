/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:03:00 by kato              #+#    #+#             */
/*   Updated: 2025/07/04 16:33:40 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			find_min(t_stack *stack);
int			find_max(t_stack *stack);

static void	push_chunk(t_stack *a, t_stack *b, int chunk_size, int *min)
{
	int	count;

	if (!a || !b || !min)
		error_exit(a, b);
	count = 0;
	while (count < chunk_size && !is_empty(a))
	{
		if (a->top && a->top->value <= *min + chunk_size)
		{
			pb(a, b);
			count++;
		}
		else
			ra(a);
	}
	*min += chunk_size;
}

static void	push_back_max(t_stack *a, t_stack *b)
{
	int	max;

	if (!a || !b)
		error_exit(a, b);
	while (!is_empty(b))
	{
		max = find_max(b);
		while (b->top && b->top->value != max)
		{
			if (b->size > 1)
				rb(b);
		}
		if (b->top)
			pa(a, b);
	}
}

void	sort_large_stack(t_stack *stack_a, t_stack *stack_b)
{
	int	chunk_size;
	int	min;

	if (!stack_a || !stack_b)
		error_exit(stack_a, stack_b);
	chunk_size = stack_a->size / 10 + 1;
	min = find_min(stack_a);
	while (!is_empty(stack_a))
		push_chunk(stack_a, stack_b, chunk_size, &min);
	push_back_max(stack_a, stack_b);
}
