/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_final.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:51:10 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:51:11 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_b_to_max(t_stack **b)
{
	int	pos;
	int	size;

	pos = get_position(*b, get_max_index(*b));
	size = stack_size(*b);
	while (pos > 0 && pos <= size / 2)
	{
		rb(b, 1);
		pos--;
	}
	while (pos < size && pos > size / 2)
	{
		rrb(b, 1);
		pos++;
	}
}

void	push_all_back(t_stack **a, t_stack **b, int pushed)
{
	while (pushed--)
	{
		rotate_b_to_max(b);
		pa(a, b, 1);
	}
}

void	final_rotate(t_stack **a)
{
	int	pos;
	int	size;

	pos = get_position(*a, get_min_index(*a));
	size = stack_size(*a);
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			ra(a, 1);
	}
	else
	{
		while (pos++ < size)
			rra(a, 1);
	}
}
