/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 03:20:58 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/07 13:01:08 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

char	*ft_match(char *splited, char *cmd)
{
	char	*path;

	if (!*cmd)
		return (NULL);
	path = ft_alphajoin(cmd, splited);
	if (ft_checkexistence(path) == 2)
		return (path);
	return (NULL);
}

char	*ft_searchandconcat(char **splited, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (splited[i])
	{
		path = ft_match(splited[i], cmd);
		if (path)
			break ;
		i++;
	}
	return (path);
}
