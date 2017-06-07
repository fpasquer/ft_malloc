/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 09:10:35 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/06 21:48:45 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
#define ENV_H

#include <sys/mman.h>
#include <stdbool.h>

#define TINY 512
#define SMALL 4096
#define LARG 0
#define NB_MAX_CONTENT 2

#define PROT_MMAP (PROT_READ | PROT_WRITE)
#define FLAG_MMAP (MAP_ANONYMOUS | MAP_PRIVATE)
#define MOD_P_SIZE(s) s + s % getpagesize()

/*
**	s_block :
**		data : Pointeur sur les data (pointeur retourne aux utilisateurs)
**		free : true si le block est libre sinon false
**		size : Taille pointeur data
**		next : Adresse du maillon suivant
**		prev : Adresse du maillon precedent
*/

typedef struct				s_block
{
	void					*data;
	bool					free;
	size_t					size;
	struct s_block			*next;
	struct s_block			*prev;
}							t_block;

typedef struct				s_malloc_env
{
	t_block					*block;
	struct s_malloc_env		*next;
	struct s_malloc_env		*prev;
}							t_malloc_env;

typedef struct				s_env
{
	t_malloc_env			*tiny;
	t_malloc_env			*small;
	t_malloc_env			*larg;
}							t_env;

#define SIZE_HEAD sizeof(t_block)

t_env						g_env;

void						*update_bloc_info(t_block *block,
		size_t size, bool free);
void						*update_bloc_ptr(t_block *block, t_block *next,
		t_block *prev);
t_block						*add_new_malloc_env(size_t size, int where);
void						show_alloc_mem(void);
bool						join_block(t_block *left, t_block *right);
bool						split_block(t_block *block_at_split, size_t size);
t_block						*find_block(void *ptr, t_malloc_env **env);
bool						set_block_avalable(t_block **block);
t_block						*find_best_block(size_t size, t_malloc_env *env,
		size_t size_env, int where);


#endif
