/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:12:40 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/06 13:18:18 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_lstlen(t_list *list)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = list;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (NULL);
	while (lst)
	{
		temp = lst;
		lst = lst->next;
	}
	return (temp);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (!new)
		return ;
	if (!*lst)
		ft_lstadd_front(lst, new);
	else
	{
		ptr = ft_lstlast((*lst));
		ptr->next = new;
	}
}
