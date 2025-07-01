/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:11:00 by kato              #+#    #+#             */
/*   Updated: 2025/07/01 16:29:49 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_stack *stack_a, t_stack *stack_b)
{
	int	value;

	if (is_empty(stack_b))
		return ;
	value = pop(stack_b);
	push(stack_a, value);
	write(1, "pa\n", 3);
}

void	pb(t_stack *stack_a, t_stack *stack_b)
{
	int	value;

	if (is_empty(stack_a))
		return ;
	value = pop(stack_a);
	push(stack_b, value);
	write(1, "pb\n", 3);
}
