/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 22:23:02 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/18 15:38:59 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"
#include <fcntl.h>

void		sha512_get_sum_string(const char *s, unsigned char sum[64])
{
	t_sha512_context	cntx_str;
	size_t				len;

	len = ft_strlen(s);
	log_info(" start get from string len = %u", len);
	sha512_init(&cntx_str);
	sha512_update(&cntx_str, (unsigned char *)s, len);
	sha512_final(&cntx_str, sum);
}

ssize_t		sha512_get_sum_file(const char *filename, unsigned char sum[64])
{
	t_sha512_context	cntx_file;
	int				fd;
	ssize_t			size;
	unsigned char	buff[SSL_SIZE_BUFF_READ];

	ft_bzero(buff, SSL_SIZE_BUFF_READ);
	log_info(" start get from file %s", filename);
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_dprintf(2, "ft_ssl: : %s: No such file or directory\n", filename);
		return (fd);
	}
	sha512_init(&cntx_file);
	while ((size = read(fd, buff, SSL_SIZE_BUFF_READ)) && size != -1)
		sha512_update(&cntx_file, buff, size);
	close(fd);
	sha512_final(&cntx_file, sum);
	return (size);
}

ssize_t		sha512_get_sum_out(unsigned char sum[64], t_bool print)
{
	t_sha512_context	cntx_file;
	ssize_t			size;
	char			buff[64];

	ft_bzero(buff, 64);
	log_info(" start get from stdout, print:%d", print);
	sha512_init(&cntx_file);
	while ((size = read(STDIN_FILENO, buff, 64)) && size != -1)
	{
		if (print)
			write(STDOUT_FILENO, buff, size);
		sha512_update(&cntx_file, (unsigned char *)buff, size);
	}
	sha512_final(&cntx_file, sum);
	return (size);
}
