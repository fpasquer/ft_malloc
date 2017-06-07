/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 21:33:07 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/06 22:15:10 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malloc.h"

void						*valloc(size_t size)
{
	int						power;
	size_t					new_size;

	power = 0;
	new_size = 1;
	while ((new_size = ft_pow(2.0, power)) > 0)
	{
		if (new_size >= size)
			break ;
		power++;
	}
	return (malloc(new_size));
}
