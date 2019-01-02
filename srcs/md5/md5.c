/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 16:56:55 by gpouyat           #+#    #+#             */
/*   Updated: 2018/12/30 23:10:26 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

int	parse_options(t_md5_flags *flags, int ac, char const *av[])
{
	int		opt;

	ft_bzero((void *)flags, sizeof(flags));
	while ((opt = ft_getopt(ac, av, "pqrs:")) != -1)
	{
		if (opt == 'p')
			flags->p = True;
		if (opt == 'q')
			flags->q = True;
		if (opt == 'r')
			flags->r = True;
		if (opt == 's')
			flags->s = True;
		if (opt == 'h')
			return (1);
		if (opt == '?')
			return (1);
	}
	return (0);
}


char	*md5(int ac, const char **av)
{
	t_md5_context	cntx;
	unsigned char	data[16];

	(void)ac;
	if (sizeof(size_t) != 8)
	{
		log_fatal("%s, sizeof(size_t): %lu", MD5_ERROR_SIZE_64, sizeof(size_t));
		return(over_str(MD5_ERROR_SIZE_64));
	}
	md5_init(&cntx);
	md5_update(&cntx, (unsigned char *)av[1], ft_strlen(av[1]));
	md5_final(&cntx, data);
    for(int i = 0; i < 16; i++) printf("%02x", data[i]);
	return (NULL);
}
