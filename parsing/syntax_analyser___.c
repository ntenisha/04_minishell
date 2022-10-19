/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser___.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntenisha <ntenisha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:08:43 by ntenisha          #+#    #+#             */
/*   Updated: 2022/10/05 02:08:03 by ntenisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_syntaxanalysis(t_list *parsresult)
{
	int	prth;
	int	start;

	start = 1;
	prth = 0;
	while (parsresult)
	{
		if (ft_syntaxcond(parsresult, &start, &prth))
			return (1);
		parsresult = parsresult->next;
	}
	if (prth)
	{
		write(2, "bash: no closing parentheses\n", 29);
		return (1);
	}
	return (0);
}
