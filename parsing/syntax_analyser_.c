/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser_.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:27:45 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/06 17:37:32 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	near_pipe_and_or(t_list *lst)
{
	int	x;

	if ((lst->type == PIPE || lst->type == AND
			|| lst->type == OR))
	{
		x = ft_getnext(lst);
		if (x == -1 || x == PIPE || x == AND
			|| x == OR || x == PRTCLOSE)
		{
			ft_errormsg(lst->splited);
			return (1);
		}
	}
	return (0);
}

int	near_openparnth(t_list *lst, int *prth)
{
	int	x;

	if (lst->type == PRTOPEN)
	{
		(*prth)++;
		x = ft_getnext(lst);
		if (x == -1 || x == PIPE || x == AND
			|| x == OR || x == PRTCLOSE)
		{
			ft_errormsg(lst->splited);
			return (1);
		}
	}
	return (0);
}

int	near_closedparnth(t_list *lst, int *prth)
{
	int	x;

	if (lst->type == PRTCLOSE)
	{
		(*prth)--;
		x = ft_getnext(lst);
		if (x == WORD || x == PRTOPEN || x == SQ
			|| x == DQ || x == WILD || x == VARIABLE)
			return (1);
	}
	return (0);
}

int	ft_wildcard(t_list *lst)
{
	int	x;

	if (lst->type == WILD)
	{
		x = ft_getnext(lst);
		if (x == PRTOPEN)
		{
			ft_errormsg(lst->splited);
			return (1);
		}
	}
	return (0);
}

void	redirectioncond(t_list *lst, int *okey, int x)
{
	if (lst->type == RDIN)
		if (x == -1 || (x != WILD && x != VARIABLE && x != WORD && x != SQ
				&& x != DQ))
			*okey = 1;
	if (lst->type == RDOUT)
		if (x == -1 || (x != WILD && x != VARIABLE && x != WORD && x != SQ
				&& x != DQ))
			*okey = 1;
	if (lst->type == RDHER)
	{
		lst->herdocexp = 0;
		if (x == -1 || (x != WILD && x != VARIABLE && x != WORD && x != SQ
				&& x != DQ))
			*okey = 1;
		else
			ft_herdoccreating(&lst);
	}
	if (lst->type == RDAPP)
		if (x == -1 || (x != WILD && x != VARIABLE && x != WORD && x != SQ
				&& x != DQ))
			*okey = 1;
}
