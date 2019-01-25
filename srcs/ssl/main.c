/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 11:31:43 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/25 16:54:05 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static t_ssl_hash	g_hashes[] = {
	{"md5", &md5},
	{"sha256", &sha256},
	{"sha512", &sha512},
	{"sha384", &sha384},
	{"sha224", &sha224},
	{NULL, NULL},
};

static int			help_full(char *cmd)
{
	if (!cmd)
		return (1);
	ft_printf("ft_ssl:Error: '%s' is an invalid command.\n", cmd);
	ft_putendl("Message Digest commands\n"
"md5               sha256            sha512\n"
"sha224            sha384\n"
"Cipher commands");
	return (1);
}

static t_ssl_hash	get_hash(const char *hash)
{
	int			index;

	index = -1;
	if (!hash)
		return ((t_ssl_hash){NULL, NULL});
	while (g_hashes[++index].buff != NULL)
		if (!ft_strcmp(g_hashes[index].buff, hash))
			break ;
	return (g_hashes[index]);
}

static t_ssl_hash	read_prompt(char **line)
{
	int			ret;
	t_ssl_hash	hash;

	*line = NULL;
	ft_putstr("ft_ssl>");
	while ((ret = get_next_line(STDIN_FILENO, line)) && ret != -1)
	{
		hash = get_hash(*line);
		if (hash.buff)
			break ;
		if (*line && **line)
			help_full(*line);
		ft_putstr("ft_ssl>");
	}
	return (hash);
}

int					main(int ac, const char **argv)
{
	char		*cmd;
	t_ssl_hash	hash;
	const char	**av;

	av = argv;
	if (INTERN_DEBUG_FT_SSL)
		log_init(".log", 2);
	if (ac <= 1)
		hash = read_prompt(&cmd);
	else
	{
		cmd = ft_strdup((char *)av[1]);
		hash = get_hash(cmd);
		++av;
		--ac;
	}
	if (hash.buff)
	{
		free(cmd);
		return (hash.f(ac, av));
	}
	help_full(cmd);
	free(cmd);
	return (-1);
}
