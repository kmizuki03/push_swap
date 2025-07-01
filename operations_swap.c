/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_swap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:10:00 by kato              #+#    #+#             */
/*   Updated: 2025/07/01 16:29:40 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_stack *stack_a)
{
	t_node	*first;
	t_node	*second;
	int		temp;

	if (stack_a->size < 2)
		return ;
	first = stack_a->top;
	second = first->next;
	temp = first->value;
	first->value = second->value;
	second->value = temp;
	write(1, "sa\n", 3);
}

void	sb(t_stack *stack_b)
{
	t_node	*first;
	t_node	*second;
	int		temp;

	if (stack_b->size < 2)
		return ;
	first = stack_b->top;
	second = first->next;
	temp = first->value;
	first->value = second->value;
	second->value = temp;
	write(1, "sb\n", 3);
}

void	ss(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a->size >= 2)
		sa(stack_a);
	if (stack_b->size >= 2)
		sb(stack_b);
	write(1, "ss\n", 3);
}
