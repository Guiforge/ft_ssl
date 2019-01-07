/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 11:31:43 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/07 18:40:27 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

int		main(int ac, const char **av)
{
	if (INTERN_DEBUG_FT_SSL)
		log_init(".log", 2);
	if (ac <= 1)
		ft_putendl(HELP_USAGE);
	if (ft_strequ("md5", av[1]))
		md5(--ac, ++av);
	else if (ft_strequ("sha256", av[1]))
		sha256(--ac, ++av);
}
