/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 16:32:19 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/04 16:34:49 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

extern char const	*g_optarg;
extern int			g_optind;

static void	sha256_exec_string(t_sha256_flags flags, t_list *lst)
{
	unsigned char sum[16];

	log_info("Start exec strings");
	while (lst)
	{
		if (!lst->content)
		{
			log_error("sha256: No string in %s:%d", __FUNCTION__, __LINE__);
			ft_dprintf(STDERR_FILENO, "sha256: No string in option s");
			return ;
		}
		sha256_get_sum_string(lst->content, sum);
		sha256_print_string(flags, sum, lst->content);
		lst = lst->next;
	}
}

static void	sha256_exec_files(t_sha256_flags flags, const char **av)
{
	unsigned char	sum[16];

	log_info("Start exec files");
	while (av && *av)
	{
		log_debug("file: %s", *av);
		if (sha256_get_sum_file(*av, sum) != -1)
			sha256_print(flags, sum, *av);
		av++;
	}
}

int			parse_options(t_sha256_flags *flags, int ac, char const *av[],
															t_list **lst_str)
{
	int		opt;

	ft_bzero((void *)flags, sizeof(flags));
	while ((opt = ft_getopt(ac, av, "pqrs:")) != -1)
	{
		if (opt == 'p')
			flags->p = True;
		if (opt == 'q')
			flags->q = True;
		if (opt == 'r')
			flags->r = True;
		if (opt == 's')
			ft_lstpush_extra_secu(lst_str, g_optarg, 42, M_LVL_FUNCT);
		if (opt == 'h' || opt == '?')
			return (1);
	}
	return (0);
}

static void	help_usage(void)
{
	ft_putendl("usage: sha256 [-pqrh] [-s [ARG]] [file ...]");
}

void		sha256(int ac, const char **av)
{
	t_sha256_flags		flags;
	t_list			*lst_str;
	unsigned char	sum[16];

	lst_str = NULL;
	if (sizeof(size_t) != 8)
	{
		log_fatal("%s, sizeof(size_t): %lu",  8, sizeof(size_t));
		return ((void)over(SSL_ERROR_SIZE_64, 0));
	}
	if (parse_options(&flags, ac, av, &lst_str))
		return (help_usage());
	if (flags.p || (!lst_str && g_optind == ac))
	{
		sha256_get_sum_out(sum, flags.p && !flags.q);
		sha256_put_sum(sum);
		ft_putchar('\n');
	}
	sha256_exec_string(flags, lst_str);
	sha256_exec_files(flags, &av[g_optind]);
	ft_secu_free_lvl(M_LVL_FUNCT);
}
