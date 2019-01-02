#include "../../includes/ft_ssl.h"

void buffer512_clean(t_buffer512 *buffer512)
{
	buffer512->buff_bytes = 0;
	ft_bzero(buffer512->buff, sizeof(buffer512->buff));
}

t_bool	buffer512_is_full(t_buffer512 *buffer512)
{
	return (buffer512->buff_bytes == MD5_BUFFER_CNTX);
}

void		buffer512_fill(t_buffer512 *buffer512, unsigned char *data, size_t size, size_t *index)
{
	unsigned char size_to_fill;

	if (!(size - *index))
	{
		log_warn("%s: Nothing to read into data", __FUNCTION__);
		return ;
	}
	size_to_fill = 64 - buffer512->buff_bytes;
	if (size_to_fill > size - *index)
		size_to_fill = (unsigned char)(size - *index);
	ft_memcpy(&buffer512->buff[buffer512->buff_bytes], &data[*index], size_to_fill);
	*index = *index + size_to_fill;
	buffer512->buff_bytes = buffer512->buff_bytes + size_to_fill;
}
