/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 00:19:11 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/06 05:42:38 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

char	**deleteit(char *var, char ***env)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	while ((*env)[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp(var, (*env)[i], ft_strlen(var))
			|| (!ft_strncmp(var, (*env)[i], ft_strlen(var)) &&
			((*env)[i][ft_strlen(var)] && (*env)[i][ft_strlen(var)] != '=')))
		{
			tmp[j] = ft_strdupb((*env)[i]);
			j++;
		}
		free((*env)[i]);
		i++;
	}
	free(*env);
	tmp[j] = NULL;
	return (tmp);
}

int	verifynamebeta(char *name)
{
	int	i;

	if (name[0] != '_' && !ft_isalpha(name[0]))
		return (-1);
	i = 1;
	while (name[i])
	{
		if (!ft_isalpha(name[i])
			&& !ft_isdigit(name[i]) && name[i] != '_')
			return (-1);
		i++;
	}
	return (i);
}

int	ft_unset(char ***env, char **cmd)
{
	int	i;
	int	err;

	i = 0;
	while (cmd[i])
	{
		err = verifynamebeta(cmd[i]);
		if (err != -1)
			*env = deleteit(cmd[i], env);
		else
			desplayerror(cmd[i]);
		i++;
	}
	return (0);
}
