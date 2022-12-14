/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser__.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:53:37 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/09 06:56:02 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_redirections(t_list *lst)
{
	int	x;
	int	okey;

	x = ft_getnext(lst);
	okey = 0;
	redirectioncond(lst, &okey, x);
	if (okey)
	{
		ft_errormsg(lst->splited);
		return (1);
	}
	return (0);
}

int	ft_quoteserror(int okey, t_list *lst)
{
	if (okey)
	{
		if (okey == 1)
			write(2, "bash: no closing quotes\n", 24);
		else
			ft_errormsg(lst->splited);
		return (1);
	}
	return (0);
}

int	ft_quotes(t_list *lst)
{
	int	x;
	int	okey;

	x = ft_getnext(lst);
	okey = 0;
	if (lst->type == DQ)
	{
		if (!ft_checksforqoutes(lst->splited, 34))
			okey = 1;
		if (x == PRTOPEN)
			okey = 2;
	}
	if (lst->type == SQ)
	{
		if (!ft_checksforqoutes(lst->splited, 39) || x == PRTOPEN)
			okey = 1;
		if (x == PRTOPEN)
			okey = 2;
	}
	if (ft_quoteserror(okey, lst))
		return (1);
	return (0);
}

int	ft_word(t_list *lst)
{
	int	x;

	if (lst->type == WORD)
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

int	ft_syntaxcond(t_list *parsresult, int *start, int *prth)
{
	if (ft_word(parsresult))
		return (1);
	if (ft_firstcheck(parsresult, start))
		return (1);
	if (near_pipe_and_or(parsresult))
		return (1);
	if (near_openparnth(parsresult, prth))
		return (1);
	if (near_closedparnth(parsresult, prth))
		return (1);
	if (ft_wildcard(parsresult))
		return (1);
	if (ft_redirections(parsresult))
		return (1);
	if (ft_quotes(parsresult))
		return (1);
	return (0);
}
