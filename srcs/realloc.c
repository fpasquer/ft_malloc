/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:23:56 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/06 22:14:55 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/env.h"
#include "../incs/ft_malloc.h"

static void *				new_addr(t_block **block, size_t size, void *ptr)
{
	size_t					i;
	char					*tmp;
	char					*new_ptr;

	if (block == NULL || (*block) == NULL)
		return (NULL);
	if ((new_ptr = (char*)malloc(size)) == NULL)
		return (ptr);
	i = 0;
	tmp = (char*)(*block)->data;
	while (i < (*block)->size && i < size)
	{
		new_ptr[i] = tmp[i];
		i++;
	}
	set_block_avalable(block);
	return (new_ptr);
}

void						*realloc(void *ptr, size_t size)
{
	t_malloc_env			*env;
	t_block					*block;

	if (ptr == NULL || (block = find_block(ptr, &env)) == NULL)
		return (malloc(size));
	if (size + SIZE_HEAD < block->size)//si on reduit le block
	{
		if (split_block(block, size + SIZE_HEAD) == true)
			set_block_avalable(&block->next);
	}
	else if (size + SIZE_HEAD > block->size)// si on augmente le block
	{
		if (block->next != NULL && block->next->free == true && size +
				SIZE_HEAD <= block->size + block->next->size)
		{
			if (join_block(block, block->next) == true)
				if (split_block(block,size + SIZE_HEAD) == true)
					set_block_avalable(&block->next);
		}
		else
			return (new_addr(&block, size, ptr));
	}
	return (ptr);
}

void						*reallocf(void *ptr, size_t size)
{
	void					*ret;

	if ((ret = realloc(ptr, size)) == NULL)
		free(ptr);
	return (ret);
}
