/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 09:46:08 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/09 07:32:00 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

void	free_built(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

char	**dupplic(char **env)
{
	char	**str;
	int		len;
	int		i;

	len = 0;
	while (env[len])
		len++;
	str = ft_malloc(sizeof(char **) * len + 1);
	if (!str)
		return (0);
	i = 0;
	while (env[i])
	{
		str[i] = ft_strdup(env[i]);
		i++;
	}
	str[i] = NULL;
	return (str);
}

void	display(char **env)
{
	char	**str;
	int		i;
	int		y;
	char	*temp;

	str = dupplic(env);
	i = -1;
	while (str[++i])
	{
		y = i + 1;
		while (str[y])
		{
			if (ft_strcmp(str[i], str[y]) > 0)
			{
				temp = str[y];
				str[y] = str[i];
				str[i] = temp;
			}
			y++;
		}
	}
	i = -1;
	while (str[++i])
		printf ("declare -x %s\n", str[i]);
}
