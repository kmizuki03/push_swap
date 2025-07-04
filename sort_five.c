/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_five.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:02:00 by kato              #+#    #+#             */
/*   Updated: 2025/07/04 16:33:40 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		find_min(t_stack *stack);
void	sort_three(t_stack *stack_a);

void	sort_five(t_stack *stack_a, t_stack *stack_b)
{
	int	min;
	int	i;

	if (!stack_a || !stack_b)
		error_exit(stack_a, stack_b);
	while (stack_a->size > 3)
	{
		min = find_min(stack_a);
		i = 0;
		while (stack_a->top && stack_a->top->value != min)
		{
			if (i < stack_a->size / 2)
				ra(stack_a);
			else
				rra(stack_a);
			i++;
		}
		if (stack_a->top)
			pb(stack_a, stack_b);
	}
	sort_three(stack_a);
	while (!is_empty(stack_b))
		pa(stack_a, stack_b);
}
