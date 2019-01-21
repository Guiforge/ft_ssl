/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digst_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 11:15:10 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/21 16:57:16 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"
#include <fcntl.h>

void		digst_get_sum_string(t_ssl_digst *digst, const char *s,\
											unsigned char sum[SSL_MAX_SUM_SIZE])
{
	size_t				len;

	len = ft_strlen(s);
	log_info(" start get from string len = %u", len);
	digst->init(digst->context);
	digst->update(digst->context, (unsigned char *)s, len);
	digst->final(digst->context, sum);
}

ssize_t		digst_get_sum_file(t_ssl_digst *digst, const char *filename,\
											unsigned char sum[SSL_MAX_SUM_SIZE])
{
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
	digst->init(digst->context);
	while ((size = read(fd, buff, SSL_SIZE_BUFF_READ)) && size != -1)
		digst->update(digst->context, buff, size);
	close(fd);
	digst->final(digst->context, sum);
	return (size);
}

ssize_t		digst_get_sum_out(t_ssl_digst *digst,\
							unsigned char sum[SSL_MAX_SUM_SIZE], t_bool print)
{
	ssize_t			size;
	char			buff[SSL_MAX_SUM_SIZE];

	ft_bzero(buff, 64);
	log_info(" start get from stdout, print:%d", print);
	digst->init(digst->context);
	while ((size = read(STDIN_FILENO, buff, 64)) && size != -1)
	{
		if (print)
			write(STDOUT_FILENO, buff, size);
		digst->update(digst->context, (unsigned char *)buff, size);
	}
	digst->final(digst->context, sum);
	return (size);
}
