/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ismatch_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 23:05:06 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/09 08:19:02 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

char	*ft_dq_sq_wrdmerging(t_list *list, char **str, int *wild)
{
	int	i;

	i = 0;
	*str = ft_replaceandjoin(str, list->splited);
	while (list->splited[i])
	{
		if (list->splited[i] == '*')
			(*wild)--;
		i++;
	}
	return (*str);
}

int	ft_ismatch(char *name, char *reg)
{
	int		i;
	int		j;
	int		x;

	i = 0;
	j = 0;
	if (!reg[0])
		return (1);
	if (reg[0] == '*')
		j = ft_partonecond(&i, reg, name);
	else
		j = ft_parttwo(&i, reg, name);
	if (j == -1)
		return (0);
	x = ft_ismatch(&name[j], &reg[i]);
	return (x);
}
