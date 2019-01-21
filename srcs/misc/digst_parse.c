/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digst_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:24:26 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/21 17:24:55 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

extern char const	*g_optarg;

int			digst_parse_options(t_ssl_digst *d, int ac, char const *av[])
{
	int		opt;

	ft_bzero(&d->flags, sizeof(d->flags));
	while ((opt = ft_getopt(ac, av, "pqrs:")) != -1)
	{
		if (opt == 'p')
			d->flags.p = True;
		if (opt == 'q')
			d->flags.q = True;
		if (opt == 'r')
			d->flags.r = True;
		if (opt == 's')
			ft_lstpush_extra_secu(&d->lst_str, g_optarg, 42, M_LVL_FUNCT);
		if (opt == 'h' || opt == '?')
			return (1);
	}
	return (0);
}
