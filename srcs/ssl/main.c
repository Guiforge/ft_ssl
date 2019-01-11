/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 11:31:43 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/11 19:50:31 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static t_ssl_hash g_hashes[] = {
	{"md5", &md5},
	{"sha256", &sha256},
	{NULL, NULL},
};

int		main(int ac, const char **av)
{
	int		index;

	index = -1;
	if (INTERN_DEBUG_FT_SSL)
		log_init("./log", 2);
	if (ac <= 1)
		ft_putendl(HELP_USAGE);
	while (g_hashes[++index].buff != NULL)
		if (!ft_strcmp(g_hashes[index].buff, av[1]))
		{
			return (g_hashes[index].f(--ac, &av[1]));
		}
}
