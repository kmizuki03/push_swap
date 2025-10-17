#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

/* Parsing */
int		ft_atoi(const char *str);
int		is_number(char *str);
int		has_duplicates(t_stack *stack);
void	parse_args(int argc, char **argv, t_stack **stack_a);

/* Stack operations */
t_stack	*stack_new(int value);
void	stack_add_back(t_stack **stack, t_stack *new);
int		stack_size(t_stack *stack);
t_stack	*stack_last(t_stack *stack);
void	free_stack(t_stack **stack);

/* Commands */
void	sa(t_stack **stack_a, int print);
void	sb(t_stack **stack_b, int print);
void	ss(t_stack **stack_a, t_stack **stack_b, int print);
void	pa(t_stack **stack_a, t_stack **stack_b, int print);
void	pb(t_stack **stack_a, t_stack **stack_b, int print);
void	ra(t_stack **stack_a, int print);
void	rb(t_stack **stack_b, int print);
void	rr(t_stack **stack_a, t_stack **stack_b, int print);
void	rra(t_stack **stack_a, int print);
void	rrb(t_stack **stack_b, int print);
void	rrr(t_stack **stack_a, t_stack **stack_b, int print);

/* Sorting */
void	sort_three(t_stack **stack_a);
void	sort_small(t_stack **stack_a, t_stack **stack_b);
void	turk_sort(t_stack **stack_a, t_stack **stack_b);

/* Utils */
int		is_sorted(t_stack *stack);
int		get_min_index(t_stack *stack);
int		get_max_index(t_stack *stack);
int		get_position(t_stack *stack, int index);
int		get_index_at_pos(t_stack *stack, int pos);
int		get_target_index(t_stack *stack_b, int index_a);
void	index_stack(t_stack **stack);
void	ft_putstr_fd(char *s, int fd);
void	error_exit(t_stack **stack_a, t_stack **stack_b);

#endif
