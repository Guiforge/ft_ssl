/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 17:43:47 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/19 18:29:21 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void		sha512_update(t_sha512_context *cntx, unsigned char *data, size_t size)
{
	size_t		index;

	index = 0;
	log_debug(" update, cntx->len: %lu, size data: %lu", cntx->len, size);
	if (!data || !size || !cntx)
	{
		log_error(" data/context invalid ptr: %#lx, size: %lu", data, size);
		return ;
	}
	buffer1024_fill(&(cntx->buffer), data, size, &index);
	while (buffer1024_is_full(&(cntx->buffer)))
	{
		buffer1024_swap64(&cntx->buffer);
		sha512_operations(cntx);
		buffer1024_clean(&(cntx->buffer));
		buffer1024_fill(&(cntx->buffer), data, size, &index);
	}
	cntx->len += size;
	if (cntx->len >= (__uint128_t)(2^128) || cntx->len < size)
	{
		log_error(" length is larger of 2^128");
		cntx->len = cntx->len & 0xffffffffffffffff;
	}
}
