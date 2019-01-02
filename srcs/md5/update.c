/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 17:43:47 by gpouyat           #+#    #+#             */
/*   Updated: 2018/12/30 19:24:17 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void			md5_update(t_md5_context *cntx, unsigned char *data, size_t size)
{
	size_t		index;

	index = 0;
	log_debug("Md5 update, cntx->len: %lu, size data: %lu", cntx->len, size);
	if (!data || !size || !cntx)
	{
		log_error("Md5 data/context invalid ptr: %#lx or size: %lu", data, size);
		return;
	}
	buffer512_fill(&(cntx->buffer), data, size, &index);
	while(buffer512_is_full(&(cntx->buffer)))
	{
		//operation
		md5_operations(cntx);
		buffer512_clean(&(cntx->buffer));
		buffer512_fill(&(cntx->buffer), data, size, &index);
	}
	cntx->len += size;
	if (cntx->len >= ULLONG_MAX || cntx->len < size)
	{
		log_error("Md5 length is larger of 2^64");
		// TODO: when length is larger of 2^64
	}
}
