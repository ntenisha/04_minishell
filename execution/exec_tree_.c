/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 05:16:32 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/06 06:21:19 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	sobuilt(char **command, char ***env)
{
	if (ft_isbuiltin(command[0]))
	{
		g_exec.returnvalue = ft_executebuiledin(command, env);
		return (1);
	}
	return (0);
}

void	soexecv(char *path, char **command, char **env)
{
	if (execve(path, command, env) < 0)
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		perror(" ");
		if (!access(path, F_OK) && access(path, X_OK))
			exit (126);
		exit(127);
	}
}

void	soisit(char *path, char **command)
{
	if (!path)
	{
		ft_nocommand(command[0]);
		exit (127);
	}
}

int	ft_simplecmd(char ***env, t_tree *tree)
{
	pid_t	id;
	char	**command;
	char	*path;
	int		status;

	command = ft_dealwithlist(tree->elements, *env);
	if (sobuilt(command, env))
		return (1);
	id = 0;
	if (g_exec.inpipe)
		id = fork();
	if (id == 0)
	{
		sig_restore();
		if (!ft_strchr(47, command[0]))
			path = ft_isacmd(command[0], *env);
		else
			path = command[0];
		soisit(path, command);
		soexecv(path, command, *env);
	}
	status = ft_getreturn(id);
	g_exec.returnvalue = ft_statushundling(status);
	return (g_exec.returnvalue);
}

int	ft_nocommand(char *line)
{
	write(2, line, ft_strlen(line));
	write(2, ": command not found\n", 20);
	g_exec.returnvalue = 127;
	return (127);
}
