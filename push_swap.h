/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:25:17 by kato              #+#    #+#             */
/*   Updated: 2025/09/24 15:59:33 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	int		size;
}	t_stack;

t_stack	*create_stack(void);
void	push(t_stack *stack, int value, int index);
int		pop(t_stack *stack);
void	clear_stack(t_stack *stack);
int		is_empty(t_stack *stack);

void	sa(t_stack *stack_a);
void	sb(t_stack *stack_b);
void	ss(t_stack *stack_a, t_stack *stack_b);
void	pa(t_stack *stack_a, t_stack *stack_b);
void	pb(t_stack *stack_a, t_stack *stack_b);
void	ra(t_stack *stack_a);
void	rb(t_stack *stack_b);
void	rr(t_stack *stack_a, t_stack *stack_b);
void	rra(t_stack *stack_a);
void	rrb(t_stack *stack_b);
void	rrr(t_stack *stack_a, t_stack *stack_b);

int		ft_atoi(const char *str);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_strlen(const char *s);
int		is_sorted(t_stack *stack);
int		has_duplicates(t_stack *stack);
int		is_valid_number(const char *str);

void	sort_stack(t_stack *stack_a, t_stack *stack_b);
void	sort_small_stack(t_stack *stack_a, t_stack *stack_b);
void	sort_large_stack(t_stack *stack_a, t_stack *stack_b);

void	error_exit(t_stack *stack_a, t_stack *stack_b);

int		find_min(t_stack *stack);
int		find_max(t_stack *stack);

void	sort_two(t_stack *stack_a);
void	sort_three(t_stack *stack_a);

void	sort_five(t_stack *stack_a, t_stack *stack_b);

void	sort_large_stack(t_stack *stack_a, t_stack *stack_b);

void	assign_indexes(t_stack *stack);
int		pop_with_index(t_stack *stack, int *index);

#endif
