/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubleexp_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 02:13:09 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/08 20:32:50 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

void	ft_returntwo(char *var, char *result, int *index)
{
	int	j;

	j = 0;
	while (var[j])
	{
		result[(*index)] = var[j];
		j++;
		(*index)++;
	}
}

void	returnexpvardq(t_list *list, char *result, char **env)
{
	char	*var;
	char	*tmp;
	int		index;

	tmp = list->splited;
	index = 0;
	list->splited++;
	while (*list->splited)
	{
		if (ft_strchr(*list->splited, "$"))
		{
			ft_outerret(list, env, &var);
			ft_returntwo(var, result, &index);
		}
		else
		{
			result[index] = *list->splited;
			index++;
		}
		list->splited++;
	}
	result[index - 1] = '\0';
	list->splited = tmp;
}

char	*ft_expand_dq(t_list *list, char **env)
{
	char	*result;

	result = ft_malloc(ft_expand_dqcount(list, env));
	returnexpvardq(list, result, env);
	return (result);
}
