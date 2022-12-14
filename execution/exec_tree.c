/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 05:04:18 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/09 09:08:16 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_getreturn(pid_t id)
{
	int	ret;

	waitpid(id, &ret, 0);
	return (ret);
}

int	ft_statushundling(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			write(2, "Quit: 3\n", 8);
		if (WTERMSIG(status) == 2)
			write(2, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	ft_isbuiltin(char *command)
{
	if (!ft_strcmp(command, "echo"))
		return (1);
	if (!ft_strcmp(command, "env"))
		return (1);
	if (!ft_strcmp(command, "pwd"))
		return (1);
	if (!ft_strcmp(command, "cd"))
		return (1);
	if (!ft_strcmp(command, "unset"))
		return (1);
	if (!ft_strcmp(command, "exit"))
		return (1);
	if (!ft_strcmp(command, "export"))
		return (1);
	return (0);
}

int	ft_executebuiledin(char **command, char ***env)
{
	if (!ft_strcmp(command[0], "echo"))
		return (ft_echo(command));
	if (!ft_strcmp(command[0], "env"))
		return (ft_env(*env));
	if (!ft_strcmp(command[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(command[0], "cd"))
		return (ft_cd(command[1], *env));
	if (!ft_strcmp(command[0], "unset"))
		return (ft_unset(env, &command[1]));
	if (!ft_strcmp(command[0], "exit"))
		return (ft_exit(&command[1]));
	if (!ft_strcmp(command[0], "export"))
		return (ft_export(&command[1], env));
	return (g_exec.returnvalue);
}

void	sig_restore(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR || \
		signal(SIGQUIT, SIG_DFL) == SIG_ERR || \
		signal(SIGTSTP, SIG_DFL) == SIG_ERR)
	{
		write(2, "sig error\n", 8);
		exit(1);
	}
}
