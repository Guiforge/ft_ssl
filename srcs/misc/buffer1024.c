/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer1024.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 15:48:11 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/18 17:57:27 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void		buffer1024_clean(t_buffer1024 *buffer1024)
{
	buffer1024->buff_bytes = 0;
	ft_bzero(buffer1024->buff, sizeof(buffer1024->buff));
}

t_bool		buffer1024_is_full(t_buffer1024 *buffer1024)
{
	log_debug("is full: %d", buffer1024->buff_bytes);
	return (buffer1024->buff_bytes == BUFFER_1024_BYTES);
}

void		buffer1024_fill(t_buffer1024 *buffer1024, unsigned char *data,
													size_t size, size_t *index)
{
	unsigned char	size_to_fill;

	if (!(size - *index))
	{
		log_warn("%s: Nothing to read into data", __FUNCTION__);
		return ;
	}
	size_to_fill = 128 - buffer1024->buff_bytes;
	if (size_to_fill > size - *index)
		size_to_fill = (unsigned char)(size - *index);
	ft_memcpy(&buffer1024->buff[buffer1024->buff_bytes], &data[*index],
																size_to_fill);
	*index = *index + size_to_fill;
	buffer1024->buff_bytes = buffer1024->buff_bytes + size_to_fill;
}
