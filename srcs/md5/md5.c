/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 16:56:55 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/07 18:39:59 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

extern char const	*g_optarg;
extern int			g_optind;

static void	md5_exec_string(t_md5_flags flags, t_list *lst)
{
	unsigned char sum[16];

	log_info("Start exec strings");
	while (lst)
	{
		if (!lst->content)
		{
			log_error("Md5: No string in %s:%d", __FUNCTION__, __LINE__);
			ft_dprintf(STDERR_FILENO, "Md5: No string in option s");
			return ;
		}
		md5_get_sum_string(lst->content, sum);
		md5_print_string(flags, sum, lst->content);
		lst = lst->next;
	}
}

static void	md5_exec_files(t_md5_flags flags, const char **av)
{
	unsigned char	sum[16];

	log_info("Start exec files");
	while (av && *av)
	{
		log_debug("file: %s", *av);
		if (md5_get_sum_file(*av, sum) != -1)
			md5_print(flags, sum, *av);
		av++;
	}
}

static int			parse_options(t_md5_flags *flags, int ac, char const *av[],
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
	ft_putendl("usage: md5 [-pqrh] [-s [ARG]] [file ...]");
}

void		md5(int ac, const char **av)
{
	t_md5_flags		flags;
	t_list			*lst_str;
	unsigned char	sum[16];

	lst_str = NULL;
	if (sizeof(size_t) != 8)
	{
		log_fatal("%s, sizeof(size_t): %lu", SSL_ERROR_SIZE_64, sizeof(size_t));
		return ((void)over(SSL_ERROR_SIZE_64, 0));
	}
	if (parse_options(&flags, ac, av, &lst_str))
		return (help_usage());
	if (flags.p || (!lst_str && g_optind == ac))
	{
		md5_get_sum_out(sum, flags.p && !flags.q);
		md5_put_sum(sum);
		ft_putchar('\n');
	}
	md5_exec_string(flags, lst_str);
	md5_exec_files(flags, &av[g_optind]);
	ft_secu_free_lvl(M_LVL_FUNCT);
}
