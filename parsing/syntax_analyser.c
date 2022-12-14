/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:47:52 by ntenisha          #+#    #+#             */
/*   Updated: 2022/09/30 14:40:10 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_checksforqoutes(char *str, int qoute)
{
	int	i;

	i = ft_strlen(str);
	if (str[i - 1] == qoute && i > 1)
		return (1);
	return (0);
}

int	ft_getnext(t_list *corrent)
{
	if (corrent->next)
	{
		if (corrent->next->type != SPACES)
			return (corrent->next->type);
		else
		{
			if (corrent->next->next)
				return (corrent->next->next->type);
		}
	}
	return (-1);
}

void	ft_errormsg(char *str)
{
	write (2, "bash: syntax error near unexpected token ", 41);
	write (2, str, ft_strlen(str));
	write (2, "\n", 1);
}

int	ft_firstcheck(t_list *lst, int *start)
{
	if (*start)
	{
		if (lst->type == PRTCLOSE || lst->type == OR
			|| lst->type == AND || lst->type == PIPE)
		{
			ft_errormsg(lst->splited);
			return (1);
		}
		*start = 0;
	}
	return (0);
}
