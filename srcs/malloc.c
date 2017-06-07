/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 08:38:22 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/06 22:14:20 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/env.h"
#include "../incs/ft_malloc.h"

/*
**	START : find_best_block
*/

/*
**	DESCRIPTION :
**		si un bloc a ete trouve ou alloue par find_best_block cette fonction
**		decoupe le block si besoin et indique de *block n'est plus libre
**	PARAM :
**		block : le block en question
**		size : la taille voulu en octet header compris
**	RETURN :
**		un pointeur sur block ou NULL
*/

static t_block				*save_not_free(t_block *block, size_t size)
{
	if (block == NULL || block->size + SIZE_HEAD < size)
		return (NULL);
	if (block->size > size)
		if (split_block(block, size) == false)
			return (NULL);
	if (update_bloc_info(block, block->size, false) == NULL)
		return (NULL);
	return (block);
}

/*
** DESCRIPTION :
**		recherche la meilleur position pour placer le bloc memmoire de taille
**		size (size doit comprendre le header) Si il n'y a pas assez de placer
**		en memoire find_best_block essai d'allouer une nouvelle plage memoire
**		en fonction de la taille demande et la taille du block, il est possible
**		que size soit revu a la hausse pour eviter les espace vide dans la
**		memoire qui ne pourront plus etre utilises
** PARAM :
**		size : nombre d'octet header compris
**	RETURN :
**		un pointeur sur le bloc qui correspond le mieux sinon NULL
**	EXEMPLE :
**		SIZE_HEAD : 40 octets
**		block libre : 124 octets donc (124 - SIZE_HEAD = 84 octets libre)
**		size demande : 45 octets (SIZE_HEAD + 5 octets) donc ft_malloc(5)
**		Une fois le block split il resterai 39 octets inutilisable, car le
**		header fait 40 octets (block - SIZE_HEAD - size demande = 124 - 40 - 45
**		= 39) Size demande passe donc de 45 a 84 pour combler ce trou
*/
t_block						*find_best_block(size_t size, t_malloc_env *env,
		size_t size_env, int where)
{
	t_block					*m;
	t_block					*start;
	t_malloc_env			*curs;

	if ((curs = env) == NULL)
		return (save_not_free(add_new_malloc_env(size_env, where), size +
				SIZE_HEAD));
	m = NULL;
	while (curs != NULL)
	{
		start = curs->block;
		while (curs->block != NULL)
		{
			if (curs->block->free == true && curs->block->size >= size)
				m = m == NULL || m->size > curs->block->size ? curs->block : m;
			curs->block = curs->block->next;
		}
		curs->block = start;
		curs = curs->next;
	}
	if (m == NULL && add_new_malloc_env(size_env, where) != NULL)
		return (find_best_block(size, env, size_env, where));
	size = m != NULL && m->size - size <= SIZE_HEAD ? m->size : size;
	return (m == NULL ? NULL : save_not_free(m, size + SIZE_HEAD));
}

/*
**	END : find_best_block
*/


void						*malloc(size_t size)
{
	t_block					*block;

	if (size + SIZE_HEAD <= TINY)
		block = find_best_block(size, g_env.tiny, TINY * NB_MAX_CONTENT, TINY);
	else if (size + SIZE_HEAD <= SMALL)
		block = find_best_block(size, g_env.small,
				SMALL * NB_MAX_CONTENT, SMALL);
	else
		block = find_best_block(size, g_env.larg, size + SIZE_HEAD, LARG);
	return (block == NULL ? NULL : block->data);
}
