/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_rotate2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:51:10 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:51:11 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exec_rotate_a(t_stack **a, int *posa, int sa)
{
	while (*posa > 0 && *posa <= sa / 2)
	{
		ra(a, 1);
		(*posa)--;
	}
	while (*posa < sa && *posa > sa / 2)
	{
		rra(a, 1);
		(*posa)++;
	}
}

void	exec_rotate_b(t_stack **b, int *posb, int sb)
{
	while (*posb > 0 && *posb <= sb / 2)
	{
		rb(b, 1);
		(*posb)--;
	}
	while (*posb < sb && *posb > sb / 2)
	{
		rrb(b, 1);
		(*posb)++;
	}
}
