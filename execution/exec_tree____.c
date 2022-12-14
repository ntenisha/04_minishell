/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree____.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:32:30 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/09 13:17:49 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	redirectionsin(t_tree *tree, char ***env)
{
	char	**filename;
	int		fd;

	filename = ft_dealwithlist(ft_copycolly(tree->redirections), *env);
	if (!filename[0][0] || filename[1])
	{
		write(2, "bash : ambiguous redirect\n", 26);
		g_exec.returnvalue = 1;
		return ;
	}
	fd = open(filename[0], O_RDONLY);
	if (fd < 0 || access(filename[0], F_OK))
	{
		write(2, "bash : No such file or directory\n", 33);
		g_exec.returnvalue = 1;
		return ;
	}
	close(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	run(tree->left, env);
	run(tree->right, env);
}

void	redirectionsout(t_tree *tree, char ***env)
{
	char	**filename;
	int		fd;

	filename = ft_dealwithlist(ft_copycolly(tree->redirections), *env);
	if (!filename[0][0] || filename[1])
	{
		write(2, "bash : ambiguous redirect\n", 26);
		g_exec.returnvalue = 1;
		return ;
	}
	fd = open(filename[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		g_exec.returnvalue = 1;
		return ;
	}
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (tree->left)
		run(tree->left, env);
	if (tree->right)
		run(tree->right, env);
}

int	redirectionsfunction(t_tree *tree, char ***env)
{
	int	fds[2];

	save_io(fds);
	if (tree->type == RDAPP)
		ft_apndredirections(tree, env);
	if (tree->type == RDHER)
		redirectionherdoc(tree, env);
	if (tree->type == RDIN)
		redirectionsin(tree, env);
	if (tree->type == RDOUT)
		redirectionsout(tree, env);
	reset_io(fds);
	return (g_exec.returnvalue);
}

int	run(t_tree *tree, char ***env)
{
	int	pfd[2];

	if (!tree)
		return (0);
	if (tree->type == LIST)
		return (ft_simplecmd(env, tree));
	if (tree->type == AND)
		return (andfunction(tree, env));
	if (tree->type == OR)
		return (orfunction(tree, env));
	if (tree->type == PIPE)
	{
		g_exec.inpipe = 0;
		leftpipefunction(tree, env, pfd);
		rightpipefunction(tree, env, pfd);
		g_exec.inpipe = 1;
		return (1);
	}
	if (!isredirections(tree->type))
		return (redirectionsfunction(tree, env));
	return (0);
}
