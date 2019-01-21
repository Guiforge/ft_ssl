/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 16:29:03 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/21 16:23:31 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void	sha384_init(t_sha512_context *cntx)
{
	if (cntx)
	{
		cntx->h0 = 0xcbbb9d5dc1059ed8;
		cntx->h1 = 0x629a292a367cd507;
		cntx->h2 = 0x9159015a3070dd17;
		cntx->h3 = 0x152fecd8f70e5939;
		cntx->h4 = 0x67332667ffc00b31;
		cntx->h5 = 0x8eb44a8768581511;
		cntx->h6 = 0xdb0c2e0d64f98fa7;
		cntx->h7 = 0x47b5481dbefa4fa4;
		buffer1024_clean(&(cntx->buffer));
		cntx->len = 0;
	}
	else
		log_fatal("Sha384: error context invalid (NULL)");
}