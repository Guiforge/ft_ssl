/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  .c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 16:32:19 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/04 16:34:49 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

int			sha512(int ac, const char **av)
{
	t_ssl_digst			d;
	t_sha512_context	c;

	d.init = (void (*) (void *))&sha512_init;
	d.update = (void (*) (void *, unsigned char *, size_t))&sha512_update;
	d.final = (void (*) (void *, unsigned char *))&sha512_final;
	d.context = &c;
	d.size_sum = 64;
	d.name = "SHA512";
	d.lst_str = NULL;
	return(digst_main(&d, ac, av));
}