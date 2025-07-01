/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:25:38 by kato              #+#    #+#             */
/*   Updated: 2025/07/01 16:28:49 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_stack *stack_a);
void	sort_five(t_stack *stack_a, t_stack *stack_b);
void	sort_large_stack(t_stack *stack_a, t_stack *stack_b);

void	sort_stack(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a->size <= 3)
		sort_three(stack_a);
	else if (stack_a->size <= 5)
		sort_five(stack_a, stack_b);
	else
		sort_large_stack(stack_a, stack_b);
}

void	sort_small_stack(t_stack *stack_a, t_stack *stack_b)
{
	sort_stack(stack_a, stack_b);
}
