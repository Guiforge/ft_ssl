/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 16:29:03 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/21 17:27:31 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void	sha256_init(t_sha256_context *cntx)
{
	if (cntx)
	{
		cntx->h0 = 0x6a09e667;
		cntx->h1 = 0xbb67ae85;
		cntx->h2 = 0x3c6ef372;
		cntx->h3 = 0xa54ff53a;
		cntx->h4 = 0x510e527f;
		cntx->h5 = 0x9b05688c;
		cntx->h6 = 0x1f83d9ab;
		cntx->h7 = 0x5be0cd19;
		buffer512_clean(&(cntx->buffer));
		cntx->len = 0;
	}
	else
		log_fatal("Sha256: error context invalid (NULL)");
}
