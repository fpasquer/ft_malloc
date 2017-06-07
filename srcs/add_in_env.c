/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_in_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 09:09:40 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/06 17:08:56 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_malloc.h"
#include "../incs/env.h"

static t_block				*add_new_malloc_env_where(size_t size,
		t_malloc_env **env)
{
	void					*ptr;
	t_malloc_env			*new;
	t_malloc_env			*curs;

	if (env == NULL || (new = (t_malloc_env*)mmap(NULL, SIZE_HEAD, PROT_MMAP,
			FLAG_MMAP, -1, 0)) == (void*)-1)
		return (NULL);
	if ((new->block = (t_block*)mmap(NULL, size, PROT_MMAP, FLAG_MMAP, -1, 0))
			== (void*)-1)
		return (NULL);
	new->prev = (*env);
	if (!((ptr = update_bloc_info(new->block, size - SIZE_HEAD, true)) ==
			update_bloc_ptr(new->block, NULL, NULL) && ptr != NULL))
		return (NULL);
	if ((curs = (*env)) == NULL)
		(*env) = new;
	else
	{
		while (curs->next != NULL)
			curs = curs->next;
		curs->next = new;
	}
	return ((*env)->block);
}

t_block						*add_new_malloc_env(size_t size, int where)
{
	t_block					*ret;

	if (where == TINY)
		ret = add_new_malloc_env_where(size, &g_env.tiny);
	else if (where == SMALL)
		ret = add_new_malloc_env_where(size, &g_env.small);
	else
		ret = add_new_malloc_env_where(size, &g_env.larg);
	return (ret);
}
