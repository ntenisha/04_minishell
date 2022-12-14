/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:52:49 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/03 13:46:30 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

int	ft_checkflag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(char **line)
{
	int	i;
	int	flag;

	flag = 1;
	while (line[flag] && !ft_checkflag(line[flag]))
		flag++;
	i = flag;
	while (line && line[i])
	{
		if (i != flag)
			write(1, " ", 1);
		write (1, line[i], ft_strlen(line[i]));
		i++;
	}
	if (flag == 1)
		write (1, "\n", 1);
	return (0);
}
