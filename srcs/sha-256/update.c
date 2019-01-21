/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 17:43:47 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/21 18:04:24 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void		sha256_update(t_sha256_context *cntx, unsigned char *data,\
																	size_t size)
{
	size_t		index;

	index = 0;
	log_debug("sha256 update, cntx->len: %lu, size data: %lu", cntx->len, size);
	if (!data || !size || !cntx)
	{
		log_error("sha256 data/context invalid ptr: %#lx, size: %lu", data, \
																		size);
		return ;
	}
	buffer512_fill(&(cntx->buffer), data, size, &index);
	while (buffer512_is_full(&(cntx->buffer)))
	{
		sha256_operations(cntx);
		buffer512_clean(&(cntx->buffer));
		buffer512_fill(&(cntx->buffer), data, size, &index);
	}
	cntx->len += size;
	if (cntx->len >= ULLONG_MAX || cntx->len < size)
	{
		log_error("sha256 length is larger of 2^64");
		cntx->len = cntx->len & 0xffffffff;
	}
}
