/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:23:00 by kato              #+#    #+#             */
/*   Updated: 2025/07/01 16:31:41 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error_exit(t_stack *stack_a, t_stack *stack_b)
{
	ft_putstr_fd("Error\n", 2);
	if (stack_a)
	{
		clear_stack(stack_a);
		free(stack_a);
	}
	if (stack_b)
	{
		clear_stack(stack_b);
		free(stack_b);
	}
	exit(1);
}
