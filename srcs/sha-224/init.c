/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 16:29:03 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/21 16:38:27 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void	sha224_init(t_sha256_context *cntx)
{
	if (cntx)
	{
		cntx->h0 = 0xc1059ed8;
		cntx->h1 = 0x367cd507;
		cntx->h2 = 0x3070dd17;
		cntx->h3 = 0xf70e5939;
		cntx->h4 = 0xffc00b31;
		cntx->h5 = 0x68581511;
		cntx->h6 = 0x64f98fa7;
		cntx->h7 = 0xbefa4fa4;
		buffer512_clean(&(cntx->buffer));
		cntx->len = 0;
	}
	else
		log_fatal("Sha224: error context invalid (NULL)");
}