/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 16:32:19 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/21 17:31:04 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

int			sha256(int ac, const char **av)
{
	t_ssl_digst			d;
	t_sha256_context	c;

	d.init = (void (*)(void *))&sha256_init;
	d.update = (void (*)(void *, unsigned char *, size_t))&sha256_update;
	d.final = (void (*)(void *, unsigned char *))&sha256_final;
	d.context = &c;
	d.size_sum = 32;
	d.name = "SHA256";
	d.lst_str = NULL;
	return (digst_main(&d, ac, av));
}
