/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:12:56 by sprodatu          #+#    #+#             */
/*   Updated: 2024/01/13 22:29:22 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_list	*newlst;
// 	t_list	*newnode;
// 	void	*newcontent;

// 	if (!lst || !del || !f)
// 		return (NULL);
// 	newlst = NULL;
// 	while (lst)
// 	{
// 		newcontent = f(lst->content);
// 		newnode = ft_lstnew(newcontent);
// 		if (!newnode)
// 		{
// 			del(newcontent);
// 			ft_lstclear(&newlst, del);
// 			return (NULL);
// 		}
// 		ft_lstadd_back(&newlst, newnode);
// 		lst = lst->next;
// 	}
// 	return (newlst);
// }

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*elem;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		elem = ft_lstnew(new_content);
		if (!elem)
		{
			del(new_content);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, elem);
		lst = lst->next;
	}
	return (new);
}
