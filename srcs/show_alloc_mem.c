/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 09:31:10 by fpasquer          #+#    #+#             */
/*   Updated: 2017/06/06 18:31:00 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/env.h"
#include "../incs/ft_malloc.h"

#define SIZE_BUFF_PRINT 500

static void					print_data(void *data, size_t size)
{
	char					*str;
	char					buff[SIZE_BUFF_PRINT];
	size_t					i;
	size_t					j;

	str = (char*)data;
	j = 0;
	while (j < size)
	{
		i = 0;
		ft_bzero(buff, SIZE_BUFF_PRINT);
		while (j < size && i < SIZE_BUFF_PRINT)
		{
			buff[i] = ft_isprint(str[j]) == true ? str[j] : '.';
			i++;
			j++;
		}
		write(STDOUT_FILENO, buff, i);
	}
}

static void					print_block(t_block *block)
{
	size_t					i;

	if (block == NULL)
		return ;
	ft_putchar('\t');
	ft_print_adr(block->data);
	ft_putstr(" - ");
	ft_print_adr(block->data + block->size);
	ft_putstr(block->free == true ? "\033[32m Free\033[0m size : " :
			"\033[0;31m Busy\033[0m size : ");
	ft_putnbr(block->size);
	if (block->free == false)
	{
		i = 0;
		ft_putstr("\n\t\tdata_val : ");
		print_data(block->data, block->size);
	}
	ft_putchar('\n');
}

static void					show_alloc_mem_where(t_malloc_env *env, char *name,
		size_t *somme_free, size_t *somme_busy)
{
	t_block					*curs_block;
	t_malloc_env			*curs_env;

	if (somme_free != NULL && somme_busy != NULL &&
			name != NULL && (curs_env = env) != NULL)
		while (curs_env != NULL && (curs_block = curs_env->block) != NULL)
		{
			ft_putstr(name);
			ft_putstr(" : ");
			ft_print_adr(curs_env->block);
			ft_putchar('\n');
			while (curs_block != NULL)
			{
				*somme_free += (curs_block->free) ? curs_block->size : 0;
				*somme_busy += (!curs_block->free) ? curs_block->size : 0;
				print_block(curs_block);
				curs_block = curs_block->next;
			}
			curs_env = curs_env->next;
		}
}

void						show_alloc_mem(void)
{
	size_t					total_free;
	size_t					total_busy;

	total_free = 0;
	total_busy = 0;
	show_alloc_mem_where(g_env.tiny, "TINY", &total_free, &total_busy);
	show_alloc_mem_where(g_env.small, "SMALL", &total_free, &total_busy);
	show_alloc_mem_where(g_env.larg, "LARG", &total_free, &total_busy);
	ft_putstr("Total free : ");
	ft_putnbr(total_free);
	ft_putstr(" octet(s) ; total busy : ");
	ft_putnbr(total_busy);
	ft_putstr(" octet(s)\n\n\n");
}
