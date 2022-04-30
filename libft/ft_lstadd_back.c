/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:31:31 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/24 11:43:47 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*next_elem;

	if (*lst == NULL)
		*lst = new;
	else
	{
		next_elem = *lst;
		while (next_elem->next != NULL)
			next_elem = next_elem->next;
		next_elem->next = new;
	}
}
