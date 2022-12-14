/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_tree___.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 05:19:31 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/08 23:45:35 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_tree	*ft_operatorsnode(t_list **parsresult, t_list *end)
{
	t_list	*tmp;
	t_list	*next;
	t_tree	*node;

	node = NULL;
	tmp = (*parsresult);
	next = ft_lastop(*parsresult, end);
	node = ft_malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = next->type;
	node->right = ft_abs(&(next->next), end);
	node->left = ft_abs(&tmp, next);
	return (node);
}

t_tree	*ft_pipes(t_list **parsresult, t_list *end)
{
	t_list	*tmp;
	t_list	*next;
	t_tree	*node;

	node = NULL;
	tmp = (*parsresult);
	next = ft_lastpipe(*parsresult, end);
	node = ft_malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = next->type;
	node->right = ft_abs(&(next->next), end);
	node->left = ft_abs(&tmp, next);
	return (node);
}

int	redirectionsnormtree(t_list *next, t_tree *node,
		t_list *end, t_list **parsresult)
{
	if (!node)
		return (1);
	if (next->type == RDHER)
	{
		node->elements = ft_malloc(sizeof(t_list *) * 2);
		if (!node->elements)
			return (1);
		node->elements[0] = next;
		node->elements[1] = NULL;
	}
	node->redirections = noderedirections(*parsresult, end);
	if (!node->redirections)
		return (1);
	return (0);
}

int	ft_protrctionone(t_tree *node)
{
	if (!node->elements)
		return (1);
	return (0);
}

int	ft_protrctiontwo(t_tree *node)
{
	if (!node->redirections)
		return (1);
	return (0);
}
