/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:43:23 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/24 18:48:00 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_elem;
	t_list	*temp;

	next_elem = *lst;
	while (next_elem != NULL)
	{
		del(next_elem->content);
		temp = next_elem;
		next_elem = next_elem->next;
		free(temp);
	}
	*lst = NULL;
}
