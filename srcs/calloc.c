/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 18:23:47 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/06 22:13:50 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malloc.h"

void						*calloc(size_t cout, size_t size)
{
	void					*ptr;
	size_t					size_total;

	size_total = size * cout;
	if ((ptr = malloc(size_total)) != NULL)
		ft_bzero(ptr, size_total);
	return (ptr);
}
