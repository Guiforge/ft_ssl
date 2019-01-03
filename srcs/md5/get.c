/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 22:23:02 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/03 13:41:35 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"
#include <fcntl.h>

void		md5_get_sum_string(const char *s, unsigned char data[16])
{
	t_md5_context	cntx_str;

	log_info("md5 start get from string, print:%d", print);
	md5_init(&cntx_str);
	md5_update(&cntx_str, (unsigned char *)s, ft_strlen(s));
	md5_final(&cntx_str, data);
}

ssize_t		md5_get_sum_file(const char *filename, unsigned char data[16])
{
	t_md5_context	cntx_file;
	int				fd;
	ssize_t			size;
	unsigned char	buff[64];

	ft_bzero(buff, 64);
	log_info("md5 start get from file %s", filename);
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_dprintf(2, "ft_ssl: md5: %s: No such file or directory\n", filename);
		return (fd);
	}
	md5_init(&cntx_file);
	while((size = read(fd, buff, 64)) && size != -1)
		md5_update(&cntx_file, buff, size);
	close(fd);
	md5_final(&cntx_file, data);
	return (size);
}

ssize_t		md5_get_sum_out(unsigned char data[16], t_bool	print)
{
	t_md5_context	cntx_file;
	ssize_t			size;
	char			buff[64];

	ft_bzero(buff, 64);
	log_info("md5 start get from stdout, print:%d", print);
	md5_init(&cntx_file);
	while((size = read(STDIN_FILENO, buff, 64)) && size != -1)
	{
		if (print)
			write(STDOUT_FILENO, buff, size);
		md5_update(&cntx_file, (unsigned char *)buff, size);
	}
	md5_final(&cntx_file, data);
	return (size);
}