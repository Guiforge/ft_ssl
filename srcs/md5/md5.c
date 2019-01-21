/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 16:56:55 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/21 16:03:35 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

int			md5(int ac, const char **av)
{
	t_ssl_digst			d;
	t_md5_context	c;

	d.init = (void (*) (void *))&md5_init;
	d.update = (void (*) (void *, unsigned char *, size_t))&md5_update;
	d.final = (void (*) (void *, unsigned char *))&md5_final;
	d.context = &c;
	d.size_sum = 16;
	d.name = "MD5";
	d.lst_str = NULL;
	return(digst_main(&d, ac, av));
}
