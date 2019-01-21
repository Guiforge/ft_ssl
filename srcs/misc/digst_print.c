/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digst_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:32:32 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/21 15:43:34 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"


static void	digst_print_prompt(t_ssl_digst *d, const char *s, t_bool is_string)
{
	if (d->flags.q || d->flags.r || !s)
		return ;
	if (is_string)
		ft_printf("%s (\"%s\") = ", d->name, s);
	else
		ft_printf("%s (%s) = ", d->name, s);
}

static void	digst_print_final(t_ssl_digst *d, unsigned char *sum,
												const char *s, t_bool is_string)
{
	digst_print_prompt(d, s, is_string);
	digst_put_sum(sum, d->size_sum);
	if (d->flags.r && !d->flags.q && s && is_string)
		ft_printf(" \"%s\"", s);
	else if (d->flags.r && !d->flags.q && s)
		ft_printf(" %s", s);
	ft_putchar('\n');
}

void		digst_print_string(t_ssl_digst *d, unsigned char *sum,
																const char *s)
{
	digst_print_final(d, sum, s, True);
}

void		digst_print(t_ssl_digst *d, unsigned char *sum, const char *s)
{
	digst_print_final(d, sum, s, False);
}

void		digst_put_sum(unsigned char *sum, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		ft_printf("%02x", sum[i]);
		i++;
	}
}
