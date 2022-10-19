/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:52:32 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/04 16:21:24 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_list	*ft_lastop(t_list *nav, t_list *end)
{
	t_list	*node;
	int		count;

	count = 0;
	node = NULL;
	while (nav != end)
	{
		if ((nav)->type == PRTOPEN)
			count++;
		if ((nav)->type == PRTCLOSE)
			count--;
		if ((nav->type == AND || nav->type == OR) && !count)
			node = nav;
		nav = nav->next;
	}
	return (node);
}

t_list	*ft_lastpipe(t_list *nav, t_list *end)
{
	t_list	*node;
	int		count;

	count = 0;
	node = NULL;
	while (nav != end)
	{
		if ((nav)->type == PRTOPEN)
			count++;
		if ((nav)->type == PRTCLOSE)
			count--;
		if (nav->type == PIPE && !count)
			node = nav;
		nav = nav->next;
	}
	return (node);
}

int	ft_size(t_list *parsresult, t_list *end)
{
	int	i;

	i = 0;
	while (parsresult != end && (parsresult->type == SPACES
			|| parsresult->type == WORD || parsresult->type == VARIABLE
			|| parsresult->type == WILD || parsresult->type == DQ
			|| parsresult->type == SQ))
	{
		if (parsresult->sqp)
			i++;
		parsresult = parsresult->next;
	}
	return (i + 1);
}

t_list	*ft_lastredr(t_list *nav, t_list *end)
{
	t_list	*node;
	int		count;

	count = 0;
	node = NULL;
	while (nav != end)
	{
		if ((nav)->type == PRTOPEN)
			count++;
		if ((nav)->type == PRTCLOSE)
			count--;
		if ((nav->type == RDAPP || nav->type == RDHER || nav->type == RDIN
				|| nav->type == RDOUT) && !count)
			node = nav;
		nav = nav->next;
	}
	return (node);
}
