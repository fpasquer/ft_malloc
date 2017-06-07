/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 08:30:45 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/07 14:39:07 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malloc.h"
#include "../incs/env.h"

int							main(void)
{
	char					*str;
	char					*str2 = NULL;
	size_t					i;
	size_t					size = 460;

	if ((str = (char*)malloc(200)) != NULL)
	{
		str2 = malloc(200);
		show_alloc_mem();
		for (i = 0; i < 199; i ++)
			str[i] = 'p';
		str[i] = '\0';
		str = realloc(str, size + 1);
		show_alloc_mem();
		free(str2);
		realloc(NULL,470);
		show_alloc_mem();
		free(str);
	}
	return (0);
}
