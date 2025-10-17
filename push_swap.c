#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		size;

	if (argc < 2)
		return (0);
	stack_a = NULL;
	stack_b = NULL;
	parse_args(argc, argv, &stack_a);
	if (is_sorted(stack_a))
	{
		free_stack(&stack_a);
		return (0);
	}
	size = stack_size(stack_a);
	index_stack(&stack_a);
	if (size == 2)
		sa(&stack_a, 1);
	else if (size == 3)
		sort_three(&stack_a);
	else if (size <= 5)
		sort_small(&stack_a, &stack_b);
	else
		turk_sort(&stack_a, &stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
