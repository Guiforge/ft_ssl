/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digst_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:42:04 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/21 15:43:32 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

extern int			g_optind;

static void	digst_exec_string(t_ssl_digst *d)
{
	unsigned char	sum[SSL_MAX_SUM_SIZE];
	t_list			*lst;

	lst = d->lst_str;
	log_info("Start exec strings");
	while (lst)
	{
		if (!lst->content)
		{
			log_error("digst: No string in %s:%d", __FUNCTION__, __LINE__);
			ft_dprintf(STDERR_FILENO, "digst: No string in option s");
			return ;
		}
		digst_get_sum_string(d, lst->content, sum);
		digst_print_string(d, sum, lst->content);
		lst = lst->next;
	}
}

static void	digst_exec_files(t_ssl_digst *d, const char **av)
{
	unsigned char	sum[SSL_MAX_SUM_SIZE];

	log_info("Start exec files");
	while (av && *av)
	{
		log_debug("file: %s", *av);
		if (digst_get_sum_file(d, *av, sum) != -1)
			digst_print(d, sum, *av);
		av++;
	}
}


static int	help_usage(const char *av[])
{
	ft_dprintf(STDERR_FILENO, "usage: %s [-pqrh] [-s [ARG]] [file ...]", av[1]);
	return (EXIT_FAILURE);
}


int		digst_main(t_ssl_digst *d, int ac, const char *av[])
{
	unsigned char	sum[SSL_MAX_SUM_SIZE];

	d->lst_str = NULL;
	if (sizeof(size_t) != 8)
	{
		log_fatal("%s, sizeof(size_t): %lu",  8, sizeof(size_t));
		return (over(SSL_ERROR_SIZE_64, EXIT_FAILURE));
	}
	if (digst_parse_options(d, ac, av))
		return (help_usage(av));
	if (d->flags.p || (!d->lst_str && g_optind == ac))
	{
		digst_get_sum_out(d, sum, d->flags.p && !d->flags.q);
		digst_put_sum(sum, d->size_sum);
		ft_putchar('\n');
	}
	digst_exec_string(d);
	digst_exec_files(d, &av[g_optind]);
	ft_secu_free_lvl(M_LVL_FUNCT);
	return (EXIT_SUCCESS);
}