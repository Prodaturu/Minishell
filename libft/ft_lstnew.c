/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:08:30 by sprodatu          #+#    #+#             */
/*   Updated: 2023/10/26 18:45:46 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->content = content;
	(*newnode).next = NULL;
	return (newnode);
}

// #include <stdlib.h>  // for malloc and NULL
// #include <stdio.h>

// typedef struct student
// {
// 	void *age;
// 	void *id;
// 	char fname;
// 	char *rank;
// 	struct student *next;
// } t_s;

// t_s *ft_lstnew(void *age, void *id, char *rank)
// {
// 	t_s *new_student;
// 	new_student = (t_s *)malloc(sizeof(t_s));
// 	if (!new_student)
// 		return (NULL);
// 	new_student->age = age;
// 	new_student->id = id;
// 	// new_student->fname = NULL;
// 	new_student->rank = rank;
// 	new_student->next = NULL;
// 	return (new_student);
// }

// int main(void)
// {
//     t_s mihai;
//     t_s john;
//     mihai.age = (void *)25;
//     mihai.id = (void *)0001;
//     mihai.fname = 'R';
//     mihai.rank = "CEO";
//     mihai.next = NULL;
//     printf("Adress of mihai: %s\n", (void *)&mihai);
//     printf("AGE: %d\n", (int)mihai.age);
//     printf("ID: %d\n", (int)mihai.id);
//     printf("Family Name: %c\n", mihai.fname);
//     printf("RANK: %s\n\n", mihai.rank);
//     john = *ft_lstnew((void *)26, (void *)0002, "CFO");
//     printf("Adress of john: %s\n", (void *)&john);
//     printf("AGE: %d\n", (int)john.age);
//     printf("ID: %d\n", (int)john.id);
//     printf("Family Name: %c\n", john.fname);
//     printf("RANK: %s\n", john.rank);
//     return (0);
// }