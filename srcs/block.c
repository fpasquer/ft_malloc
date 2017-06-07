/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 09:18:46 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/07 15:13:25 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/env.h"
#include "../incs/ft_malloc.h"

/*
**	DESCRIPTION :
**		decoupe le bloc 'block_at_split' en 2 blocks. Le bloc de gauche aura
**		la taille size. Les pointeurs next et prev de block_at_split et du reste
**		sont mit a jour
**	PARAM :
**		block_at_split : adresse du block qui doit etre decoupe
**		size : taille voulu du bloc block_at_split header compris
**	RETURN :
**		true si la decoupe est ok sinon false
*/

bool						split_block(t_block *block_at_split, size_t size)
{
	void					*ptr;
	bool					free;
	size_t					mem;
	t_block					*tmp;
	t_block					*next;

	if (block_at_split == NULL || block_at_split->size < size)
		return (false);
	mem = block_at_split->size;
	free = block_at_split->free;
	tmp = (void*)block_at_split->data + size - SIZE_HEAD;
	next = block_at_split->next;
	if ((ptr = update_bloc_info(block_at_split, size - SIZE_HEAD,
			block_at_split->free)) == update_bloc_ptr(block_at_split, tmp,
			block_at_split->prev) && ptr != NULL)
		if ((ptr = update_bloc_info(block_at_split->next,
				mem - size, free)) == update_bloc_ptr(
				block_at_split->next, next,
				block_at_split) && ptr != NULL)
			return (true);
	return (false);
}

/*
**	DESCRIPTION :
**		Ajoute la taille du block de droite au block de gauche. Change le
**		pointeur left->next pour lui donner la valeur de right->next
**		le block left ets le block a conserver
**	PARAM :
**		left : block de gauche dans  liste chainee
**		right : block de droite dans la liste chainee
**	RETOUR :
**		true si left et right sont different de NULL sinon false
*/

bool						join_block(t_block *left, t_block *right)
{
	if (left == NULL || right == NULL)
		return (false);
	left->size += right->size + SIZE_HEAD;
	left->next = right->next;
	return (true);
}

void						*update_bloc_info(t_block *block,
		size_t size, bool free)
{
	if (block == NULL)
		return (NULL);
	block->data = (void*)block + SIZE_HEAD;
	block->size = size;
	block->free = free;
	return (block->data);
}

void						*update_bloc_ptr(t_block *block, t_block *next,
		t_block *prev)
{
	if (block == NULL)
		return (NULL);
	block->next = next;
	block->prev = prev;
	return (block->data);
}
