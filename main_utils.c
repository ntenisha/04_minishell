/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:31:46 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/08 16:32:19 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	reset_io(int io[2])
{
	if (dup2(io[0], STDIN_FILENO) == -1 || dup2(io[1], STDOUT_FILENO) == -1)
		perror(NULL);
}

void	save_io(int io[2])
{
	io[0] = dup(STDIN_FILENO);
	io[1] = dup(STDOUT_FILENO);
	if (io[0] == -1 || io[1] == -1)
		perror(NULL);
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void	itsnull(char **newenv)
{
	char		*sr_cap;

	sr_cap = tgetstr("sr", NULL);
	tputs(sr_cap, 0, ft_putchar);
	printf("$> exit\n");
	cleartrush();
	free(newenv);
	exit (g_exec.returnvalue);
}

void	cleartrush(void)
{
	t_trush	*tmp;

	while (g_exec.trush)
	{
		tmp = g_exec.trush;
		g_exec.trush = g_exec.trush->next;
		free(tmp->element);
		tmp->element = NULL;
		free(tmp);
		tmp = NULL;
	}
	g_exec.trush = NULL;
}
