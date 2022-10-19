/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:32:58 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/07 03:30:59 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

void	ft_cleanexport(int line, char ***env, char *cmd)
{
	char	*tmp;

	if (line != -1)
	{
		tmp = (*env)[line];
		if (!ft_strchr('=', cmd))
			return ;
		(*env)[line] = ft_strdupb(cmd);
		free(tmp);
	}
	else
		*env = vars_notexist(cmd, env);
}

char	**ft_wildrgex(char *pattern)
{
	struct dirent	*ret;
	DIR				*dir;
	int				i;
	char			**names;

	i = -1;
	names = ft_malloc(sizeof(char *) * ft_nbfilestwo(pattern));
	dir = opendir(".");
	if (!dir)
		return (NULL);
	ret = readdir(dir);
	while (ret != NULL)
	{
		if ((ret->d_type == DT_DIR || ret->d_type == DT_REG)
			&& ret->d_name[0] != '.' && ft_ismatch(ret->d_name, pattern))
			names[++i] = ft_strdup(ret->d_name);
		ret = readdir(dir);
	}
	names[++i] = NULL;
	closedir(dir);
	return (names);
}

char	**ft_wildcard_(char *pattern)
{
	char	**names;

	if (ft_strlen(pattern) == 1)
	{
		names = ft_simplewild();
		names = ft_returngiven(names, pattern);
	}
	else
	{
		names = ft_wildrgex(pattern);
		names = ft_returngiven(names, pattern);
	}
	return (names);
}
