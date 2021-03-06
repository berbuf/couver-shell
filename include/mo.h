/*
** mo.h for 42sh in /home/hedia_m/couver-shell/minishell2
**
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
**
** Started on  Fri May 20 22:26:56 2016 mohamed-laid hedia
** Last update Sun Jun  5 03:45:35 2016 vincent riamon
*/

#ifndef MO_H_
# define MO_H_

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "shell.h"
# include "my.h"

typedef struct	s_pipe
{
  int		i;
  int		p[1][2];
}		t_pipe;

typedef struct	s_command
{
  int		save[2];
  int		failed;
  int		op;
  int		i;
}		t_command;

/* minishell2.c */

void            the_execution(char **tab, t_shell *env);

/* pars.c */

int		is_valide(char **tab, t_shell *sh);
void		pipe_builtin(char **b, t_shell *env, t_pipe *p, t_command *s);
int		length_param(char **tab, int i);
char		**pars_param(char **tab, int i, t_shell *sh);

/* pipe.c */

int		wait_process(t_command *s, t_pipe *p, int ret);
void		do_fork(char **tab, t_shell *env, t_pipe *p);
void		last_process(char **tab, t_shell *env, t_command *s, t_pipe *p);
void		do_process(char **tab, t_shell *env, t_command *s, t_pipe *p);
void		pipe_execution(char **tab, t_shell *env, t_command *s);

/* redirections.c */

void		write_on_pipe(int fd, char *file);
int		double_left_redirection(char *red, char *file);
int		left_redirectin(char *red, char *file);
int		double_right_redirection(char *red, char *file);
int		right_redirection(char *red, char *file);

/* verif_return.c */

int		verif_one_sig(int st, t_command *s);
int		verif_sig(int st, int *t, t_command *s);
int		verif_ret_pipe(int *f, t_command *s, t_pipe *p, int ret);

/* verifs.c */

int		next_is_pipe(char **tab, int i);
int		is_sep_param(char *str);
int		is_redirection(char *str);
int		is_builtin(char *str);

/* get_line */

char		*get_next_line(const int fd);

/* inhibitors.c */

void	check_inhibitors(char **tab);
char	**delete_inhibitors(char **tab);
void	add_to_str(char **tab, int i);
char	*inhibitors_file(char *file);

/* which.c */

int	my_which(char **tab, t_shell *sh);
int	my_where(char **tab, t_shell *sh);
char	**my_path_tab(t_shell *sh);
int	check_in_path(char *str, char **tab_path, int o);

#endif  /* !MO_H_ */
