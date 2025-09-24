/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:03:00 by kato              #+#    #+#             */
/*   Updated: 2025/09/24 16:06:28 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			find_min(t_stack *stack);
int			find_max(t_stack *stack);

static void	push_top_or_rotate(t_stack *a, t_stack *b, int chunk_max,
		int *pushed)
{
	if (a->top && a->top->index <= chunk_max)
	{
		if (a->top->index < chunk_max - (chunk_max / 2))
		{
			pb(a, b);
			rb(b);
		}
		else
		{
			pb(a, b);
		}
		(*pushed)++;
	}
	else
	{
		ra(a);
	}
}

static int	get_max_index_pos(t_stack *b, int max_index)
{
	int		pos;
	t_node	*cur;

	pos = 0;
	cur = b->top;
	while (cur)
	{
		if (cur->index == max_index)
			return (pos);
		cur = cur->next;
		pos++;
	}
	return (-1);
}

static void	push_back_max(t_stack *a, t_stack *b)
{
	int	max_index;
	int	pos;

	while (!is_empty(b))
	{
		max_index = b->size - 1;
		pos = get_max_index_pos(b, max_index);
		if (pos <= b->size / 2)
			while (b->top->index != max_index)
				rb(b);
		else
			while (b->top->index != max_index)
				rrb(b);
		pa(a, b);
	}
}

static void	process_chunks(t_stack *a, t_stack *b, int total, int chunk_size)
{
	int	next_chunk;
	int	pushed;
	int	count;

	pushed = 0;
	next_chunk = chunk_size - 1;
	while (pushed < total)
	{
		count = 0;
		while (count < a->size && pushed < total)
		{
			push_top_or_rotate(a, b, next_chunk, &pushed);
			count++;
		}
		next_chunk += chunk_size;
		if (next_chunk >= total)
			next_chunk = total - 1;
	}
}

void	sort_large_stack(t_stack *stack_a, t_stack *stack_b)
{
	int	chunk_size;
	int	total;

	total = stack_a->size;
	if (total <= 100)
		chunk_size = 10;
	else
		chunk_size = 35;
	process_chunks(stack_a, stack_b, total, chunk_size);
	push_back_max(stack_a, stack_b);
}
