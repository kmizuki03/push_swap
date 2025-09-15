/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:03:00 by kato              #+#    #+#             */
/*   Updated: 2025/07/18 20:30:40 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			find_min(t_stack *stack);
int			find_max(t_stack *stack);

static void	push_chunk(t_stack *a, t_stack *b, int chunk_max, int *pushed,
		int total)
{
	int	count;
	int	size;

	count = 0;
	size = a->size;
	while (count < size && *pushed < total)
	{
		if (a->top && a->top->index <= chunk_max)
		{
			// bの中央より小さい値はpb後rbで下に送る
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
		count++;
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
	int max_index, pos;
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

void	sort_large_stack(t_stack *stack_a, t_stack *stack_b)
{
	int	chunk_size;
	int	total;
	int	next_chunk;
	int	pushed;

	total = stack_a->size;
	pushed = 0;
	// チャンクサイズを動的に調整
	if (total <= 100)
		chunk_size = 10;
	else
		chunk_size = 35;
	next_chunk = chunk_size - 1;
	while (pushed < total)
	{
		push_chunk(stack_a, stack_b, next_chunk, &pushed, total);
		next_chunk += chunk_size;
		if (next_chunk >= total)
			next_chunk = total - 1;
	}
	push_back_max(stack_a, stack_b);
}
