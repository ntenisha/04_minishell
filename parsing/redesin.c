/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redesin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:31:30 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/04 20:51:49 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	isredirections(int type)
{
	if (type == RDAPP || type == RDHER || type == RDIN || type == RDOUT)
		return (0);
	return (1);
}

int	isnextaword(t_list *lst)
{
	if (lst->type == WORD || lst->type == WILD)
		return (0);
	return (1);
}

t_list	*ft_createnodes(t_list *lst)
{
	t_list	*node;

	node = ft_malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->nb = lst->nb;
	node->herdocexp = lst->herdocexp;
	node->splited = lst->splited;
	node->sqp = lst->sqp;
	node->type = lst->type;
	node->nb = lst->nb;
	node->next = NULL;
	return (node);
}

int	ft_redirectiononecon(t_list *lst)
{
	return (lst
		&& lst->type != PIPE
		&& lst->type != OR
		&& lst->type != AND
		&& lst->type != PRTOPEN
		&& lst->type != PRTCLOSE);
}

int	ft_isthatared(t_list *lst)
{
	return (lst->type == RDAPP
		|| lst->type == RDHER
		|| lst->type == RDIN
		|| lst->type == RDOUT);
}
