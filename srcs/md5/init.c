/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 17:41:02 by gpouyat           #+#    #+#             */
/*   Updated: 2018/12/30 17:45:09 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void	md5_init(t_md5_context *cntx)
{
	if (cntx)
	{	
		cntx->h0 = 0x67452301;
		cntx->h1 = 0xEFCDAB89;
		cntx->h2 = 0x98BADCFE;
		cntx->h3 = 0x10325476;
		ft_bzero(cntx->buffer, sizeof(cntx->buffer));
		cntx->len = 0;
		cntx->buff_bytes = 0;
	}
	else
		log_fatal("Md5: error context invalid (NULL)");
}