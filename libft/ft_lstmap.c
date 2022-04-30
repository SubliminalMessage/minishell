/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:47:46 by dangonza          #+#    #+#             */
/*   Updated: 2022/01/24 18:48:39 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*root;
	t_list	*next_node;

	if (!lst)
		return (NULL);
	root = ft_lstnew(f(lst->content));
	if (root != NULL)
	{
		next_node = root;
		lst = lst->next;
		while (lst != NULL)
		{
			next_node->next = ft_lstnew(f(lst->content));
			if (next_node == NULL)
			{
				ft_lstclear(&root, del);
				return (NULL);
			}
			lst = lst->next;
			next_node = next_node->next;
		}
	}
	return (root);
}
