/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 15:14:43 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/07 15:12:47 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/env.h"
#include "../incs/ft_malloc.h"

static t_block				*find_block_in_env(void *ptr, t_malloc_env *env,
		t_malloc_env **in_env)
{
	t_block					*curs_b;
	t_malloc_env			*curs_env;

	if ((curs_env = env) != NULL && in_env != NULL)
		while (curs_env != NULL)
		{
			(*in_env) = curs_env;
			curs_b = curs_env->block;
			while (curs_b != NULL)
			{
				if (curs_b->data == ptr)
					return (curs_b);
				curs_b = curs_b->next;
			}
			curs_env = curs_env->next;
		}
	return (NULL);
}

t_block						*find_block(void *ptr, t_malloc_env **env)
{
	t_block					*ret;

	if (env == NULL)
		return (NULL);
	if ((ret = find_block_in_env(ptr, g_env.tiny, env)) != NULL)
		return (ret);
	if ((ret = find_block_in_env(ptr, g_env.small, env)) != NULL)
		return (ret);
	if ((ret = find_block_in_env(ptr, g_env.larg, env)) != NULL)
		return (ret);
	(*env) = NULL;
	return (NULL);
}
