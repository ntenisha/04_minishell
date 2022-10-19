/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree__.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:07:16 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/07 04:32:25 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_sizetablered(t_list *redirection)
{
	int	i;

	i = 0;
	while (redirection)
	{
		i++;
		redirection = redirection->next;
	}
	return (i + 1);
}

t_list	**ft_copycolly(t_list *redirection)
{
	t_list	**elm;
	int		i;

	elm = ft_malloc(ft_sizetablered(redirection) * sizeof(t_list *));
	i = 0;
	while (redirection)
	{
		elm[i] = redirection;
		i++;
		redirection = redirection->next;
	}
	elm[i] = NULL;
	return (elm);
}

int	andfunction(t_tree *tree, char ***env)
{
	run(tree->left, env);
	if (g_exec.returnvalue == 0)
		return (run(tree->right, env));
	return (g_exec.returnvalue);
}

int	orfunction(t_tree *tree, char ***env)
{
	run(tree->left, env);
	if (g_exec.returnvalue != 0)
		return (run(tree->right, env));
	return (g_exec.returnvalue);
}

void	leftpipefunction(t_tree *tree, char ***env, int *pfd)
{
	int	ret;

	if (pipe(pfd) == -1)
	{
		g_exec.returnvalue = 1;
		exit(1);
	}
	ret = fork();
	if (ret == -1)
	{
		g_exec.returnvalue = 1;
		exit(1);
	}
	else if (ret == 0)
	{
		close(STDOUT_FILENO);
		close(pfd[IN]);
		dup2(pfd[OUT], STDOUT_FILENO);
		close(pfd[OUT]);
		run(tree->left, env);
		exit(0);
	}
}
