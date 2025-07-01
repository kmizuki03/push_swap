/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_reverse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:13:00 by kato              #+#    #+#             */
/*   Updated: 2025/07/01 16:30:20 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_stack *stack_a)
{
	t_node	*last;
	t_node	*second_last;

	if (stack_a->size < 2)
		return ;
	last = stack_a->top;
	second_last = NULL;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = stack_a->top;
	stack_a->top = last;
	write(1, "rra\n", 4);
}

void	rrb(t_stack *stack_b)
{
	t_node	*last;
	t_node	*second_last;

	if (stack_b->size < 2)
		return ;
	last = stack_b->top;
	second_last = NULL;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = stack_b->top;
	stack_b->top = last;
	write(1, "rrb\n", 4);
}

void	rrr(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a->size >= 2)
		rra(stack_a);
	if (stack_b->size >= 2)
		rrb(stack_b);
	write(1, "rrr\n", 4);
}
