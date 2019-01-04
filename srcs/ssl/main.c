/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 11:31:43 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/04 15:47:23 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

int		main(int ac, const char **av)
{
	if (INTERN_DEBUG_FT_SSL)
		log_init(".log", 2);
	if (ac <= 1)
		ft_putendl(HELP_USAGE);
	md5(--ac, ++av);
}
