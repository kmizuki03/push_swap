/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:25:12 by kato              #+#    #+#             */
/*   Updated: 2025/09/24 15:59:32 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_stack(t_stack *stack_a, int argc, char **argv)
{
	int	i;
	int	num;

	if (!stack_a || !argv)
		error_exit(stack_a, NULL);
	i = argc - 1;
	while (i > 0)
	{
		if (!is_valid_number(argv[i]))
			error_exit(stack_a, NULL);
		num = ft_atoi(argv[i]);
		if (num == 0 && argv[i][0] != '0')
			error_exit(stack_a, NULL);
		push(stack_a, num, 0);
		i--;
	}
	assign_indexes(stack_a);
}

static void	check_duplicates(t_stack *stack_a, t_stack *stack_b)
{
	if (!stack_a)
		error_exit(stack_a, stack_b);
	if (has_duplicates(stack_a))
		error_exit(stack_a, stack_b);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2 || !argv)
		return (0);
	stack_a = create_stack();
	stack_b = create_stack();
	if (!stack_a || !stack_b)
		error_exit(stack_a, stack_b);
	init_stack(stack_a, argc, argv);
	check_duplicates(stack_a, stack_b);
	if (!is_sorted(stack_a))
		sort_stack(stack_a, stack_b);
	clear_stack(stack_a);
	clear_stack(stack_b);
	free(stack_a);
	free(stack_b);
	return (0);
}
