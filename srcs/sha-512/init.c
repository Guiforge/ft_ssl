/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 16:29:03 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/21 17:32:46 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void	sha512_init(t_sha512_context *cntx)
{
	if (cntx)
	{
		cntx->h0 = 0x6a09e667f3bcc908;
		cntx->h1 = 0xbb67ae8584caa73b;
		cntx->h2 = 0x3c6ef372fe94f82b;
		cntx->h3 = 0xa54ff53a5f1d36f1;
		cntx->h4 = 0x510e527fade682d1;
		cntx->h5 = 0x9b05688c2b3e6c1f;
		cntx->h6 = 0x1f83d9abfb41bd6b;
		cntx->h7 = 0x5be0cd19137e2179;
		buffer1024_clean(&(cntx->buffer));
		cntx->len = 0;
	}
	else
		log_fatal("Sha512: error context invalid (NULL)");
}
