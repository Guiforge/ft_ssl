/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 11:31:43 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/21 16:18:22 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static t_ssl_hash g_hashes[] = {
	{"md5", &md5},
	{"sha256", &sha256},
	{"sha512", &sha512},
	{"sha384", &sha384},
	{NULL, NULL},
};

static int		help_full(int ac, const char **av)
{
	if (ac <= 1)
		return (1);
	ft_printf("ft_ssl:Error: '%s' is an invalid command.\n", av[1]);
	ft_putendl("Message Digest commands\n"
"md5               sha256            sha512            whirlpool\n"
"Cipher commands");
	return(1);
}

int		main(int ac, const char **av)
{
	int		index;

	index = -1;
	if (INTERN_DEBUG_FT_SSL)
		log_init(".log", 2);
	if (ac <= 1)
		ft_putendl(HELP_USAGE);
	while (g_hashes[++index].buff != NULL)
		if (!ft_strcmp(g_hashes[index].buff, av[1]))
		{
			return (g_hashes[index].f(--ac, &av[1]));
		}
	return(help_full(ac, av));
}
