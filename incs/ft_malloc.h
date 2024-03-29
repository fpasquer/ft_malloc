/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 14:44:58 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/07 15:24:21 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"

void						*malloc(size_t size);
void						free(void *ptr);
void						*realloc(void *ptr, size_t size);
void						*reallocf(void *ptr, size_t size);
void						*calloc(size_t cout, size_t size);
void						*valloc(size_t size);
void						show_alloc_mem(void);

#endif
