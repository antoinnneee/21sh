/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 11:47:18 by abureau           #+#    #+#             */
/*   Updated: 2016/12/15 12:35:25 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "../libft/includes/libft.h"
#include "../includes/get_next_line.h"
#include <stdlib.h>
#include "../includes/minishell.h"

void		clear_term(int argc, char **argv)
{
	argc = 0;
	argv = NULL;
	ft_putstr("\033[2J\033[1;1H\033[32mminsh:>\033[0m ");
}

t_cmd		*parse_command(char *tmp, t_msh *msh)
{
	t_cmd	*cmd;
	char	*commande;

	commande = ft_strtrim(tmp);
	free(tmp);
	cmd = NULL;
	if (commande)
		if (!ft_strcmp(commande, ""))
		{
			free(commande);
			return (NULL);
		}
		else
		{
			cmd = split_cmd(commande);
			if (!cmd)
			{
				ft_putstr(commande);
				ft_putendl(": command not found");
			}
			check_env(&cmd, msh);
			return (cmd);
		}
	else
		return (NULL);
}

t_cmd		*cmd_setter(char *commande, t_msh *msh)
{
	char	**c_split;
	c_split = ft_strsplit(ft_strtrim(commande), ";");
	
}

int			main(int argc, char **argv, char **environ)
{
	char	**buf;
	t_msh	*msh;
	t_cmd	*cmd;

	clear_term(argc, argv);
	msh = copy_env(environ);
	inimain(&msh);
	buf = (char**)ft_memalloc(sizeof(char*));
	setup_catch();
	fb(&buf, 0);
	while (get_next_line(0, buf))
	{
		if (*buf)
		{
			if ((cmd = parse_command(*buf, msh)))
			{
				exec_cmd(&cmd, &msh, NULL);
				print_detail_cmd(cmd);
			}
		}
		free_cmd(cmd);
		ft_putstr("\x1B[32mminsh:>\x1B[0m ");
	}
	free_path();
	return (0);
}

static void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		ft_putstr("\x1B[32mminsh:>\x1B[0m ");
		//		run_exit(NULL, (t_msh*)set_add_msh(0, 0));
	}
}

void		setup_catch(void)
{
	if (signal(SIGINT, sig_handler) == SIG_ERR)
	{
		ft_putendl("SIGNAL CATCH ERROR");
	}
}
