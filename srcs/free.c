/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 15:09:44 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/06 22:29:05 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/env.h"
#include "../incs/ft_malloc.h"

static bool					check_env_block(t_malloc_env **env)
{
	t_malloc_env			*prev;
	t_malloc_env			*next;

	if (env == NULL || (*env) == NULL)
		return (false);
	if ((*env)->block->next == NULL && (*env)->block->prev == NULL &&
			(*env)->block->free == true)
	{
		next = (*env)->next;
		prev = (*env)->prev;
		munmap((*env)->block, (*env)->block->size + SIZE_HEAD);
		(*env)->block = NULL;
		if ((*env) == g_env.tiny)
			g_env.tiny = next;
		else if ((*env) == g_env.small)
			g_env.small = next;
		else if ((*env) == g_env.larg)
			g_env.larg = next;
		munmap((*env), SIZE_HEAD);
		if (prev != NULL)
			prev->next = next;
		if (next != NULL)
			next->prev = prev;
	}
	return (true);
}

/*
**	START : set_block_avalable
*/

/*
**	DESCRIPTION :
**		indique a l'environnement de malloc que ce block est libre. Si le block
**		de gauche ou droit ets libre, fusionne les blocks pour en faire 1
**	PARAM :
**		block : block concerne
**	RETOUR :
**		true si success ou false
*/
bool						set_block_avalable(t_block **block)
{
	if (block == NULL || *block == NULL || (*block)->free != false)
		return (false);
	(*block)->free = true;
	if ((*block)->prev != NULL && (*block)->prev->free == true)
	{
		if (join_block((*block)->prev, (*block)) == false)
			return (false);
		(*block) = (*block)->prev;
	}
	if ((*block)->next != NULL && (*block)->next->free == true)
		if (join_block((*block), (*block)->next) == false)
			return (false);
	return (true);
}

/*
**	END : set_block_avalable
*/

void						free(void *ptr)
{
	t_block					*block;
	t_malloc_env			*env;

	env = NULL;
	if (ptr != NULL && (block = find_block(ptr, &env)) == NULL)
	{
		ft_putstr("L'adresse : ");
		ft_print_adr(ptr);
		ft_putstr(" n'a pas ete allouee ou est deja free\n");
		;
	}
	else if (ptr != NULL)
	{
		set_block_avalable(&block);
		check_env_block(&env);
	}
}
