/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:01:00 by kato              #+#    #+#             */
/*   Updated: 2025/07/01 16:35:39 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_stack *stack_a)
{
	if (stack_a->top->value > stack_a->top->next->value)
		sa(stack_a);
}

static void	sort_three_case1(t_stack *stack_a, int first, int second, int third)
{
	if (first > second && second < third && third > first)
		sa(stack_a);
	else if (first > second && second > third)
	{
		sa(stack_a);
		rra(stack_a);
	}
}

static void	sort_three_case2(t_stack *stack_a, int first, int second, int third)
{
	if (first > second && second < third && third < first)
		ra(stack_a);
	else if (first < second && second > third && third > first)
	{
		sa(stack_a);
		ra(stack_a);
	}
	else if (first < second && second > third && third < first)
		rra(stack_a);
}

static void	sort_three_dispatch(t_stack *stack_a, int first, int second,
		int third)
{
	sort_three_case1(stack_a, first, second, third);
	sort_three_case2(stack_a, first, second, third);
}

void	sort_three(t_stack *stack_a)
{
	int	first;
	int	second;
	int	third;

	if (stack_a->size == 2)
	{
		sort_two(stack_a);
		return ;
	}
	first = stack_a->top->value;
	second = stack_a->top->next->value;
	third = stack_a->top->next->next->value;
	sort_three_dispatch(stack_a, first, second, third);
}
