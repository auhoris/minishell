/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:30:48 by auhoris           #+#    #+#             */
/*   Updated: 2021/01/23 18:20:29 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_el)
{
	t_list	*start;

	start = *lst;
	if (!(*lst))
	{
		*lst = new_el;
		return ;
	}
	while (start->next)
		start = start->next;
	start->next = new_el;
}
