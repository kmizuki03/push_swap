/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:51:10 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:51:11 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	calc_moves(int pos, int size)
{
	if (pos <= size / 2)
		return (pos);
	return (size - pos);
}

static int	calc_combined_cost(int cost_a, int cost_b, int pos_a, int pos_b,
		int size_a, int size_b)
{
	if ((pos_a <= size_a / 2 && pos_b <= size_b / 2) || (pos_a > size_a / 2
			&& pos_b > size_b / 2))
	{
		if (cost_a > cost_b)
			return (cost_a);
		return (cost_b);
	}
	return (cost_a + cost_b);
}

int	calc_cost(t_stack *a, t_stack *b, int pos_a)
{
	int	idx_a;
	int	pos_b;
	int	size_a;
	int	size_b;
	int	cost_a;
	int	cost_b;

	idx_a = get_index_at_pos(a, pos_a);
	pos_b = get_position(b, get_target_index(b, idx_a));
	size_a = stack_size(a);
	size_b = stack_size(b);
	cost_a = calc_moves(pos_a, size_a);
	cost_b = calc_moves(pos_b, size_b);
	return (calc_combined_cost(cost_a, cost_b, pos_a, pos_b, size_a, size_b));
}

int	find_cheap(t_stack *a, t_stack *b)
{
	int	size;
	int	cheap_pos;
	int	cheap_cost;
	int	i;
	int	cost;

	size = stack_size(a);
	cheap_pos = 0;
	cheap_cost = calc_cost(a, b, 0);
	i = 1;
	while (i < size)
	{
		cost = calc_cost(a, b, i);
		if (cost < cheap_cost)
		{
			cheap_cost = cost;
			cheap_pos = i;
		}
		i++;
	}
	return (cheap_pos);
}
