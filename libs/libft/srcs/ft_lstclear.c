/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:41:45 by auhoris           #+#    #+#             */
/*   Updated: 2020/11/03 21:10:26 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*sv_lst;

	if (!(*lst))
		return ;
	while (*lst)
	{
		sv_lst = *lst;
		*lst = (*lst)->next;
		(*del)(sv_lst->content);
		free(sv_lst);
	}
	*lst = 0;
}
