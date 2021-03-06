/*
** pipe.c for 42sh in /home/hedia_m/couver-shell
**
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
**
** Started on  Sun May 22 21:19:49 2016 mohamed-laid hedia
** Last update Sun Jun  5 17:55:25 2016 mohamed-laid hedia
*/

#include "mo.h"

int		wait_process(t_command *s, t_pipe *p, int ret)
{
  int		*f;
  int		i;

  if ((f = malloc(sizeof(int) * (p->i + 1))) == NULL)
    return (-1);
  i = 0;
  while (i < p->i)
    {
      wait(&f[i]);
      i = i + 1;
    }
  return (verif_ret_pipe(f, s, p, ret));
}

void		do_fork(char **b, t_shell *env, t_pipe *p)
{
  int		f;

  if ((f = fork()) == -1)
    return ;
  else if (f == 0)
    {
      if (dup2(p->p[p->i % 2][0], 0) == -1)
	exit(fprintf(stderr, "%s\n", strerror(errno)) * 0 + 1);
      close(p->p[p->i % 2][0]);
      close(p->p[p->i % 2][1]);
      if (minishell1(b, env) == -1)
	exit(EXIT_FAILURE);
    }
}

void		last_process(char **tab, t_shell *env, t_command *s, t_pipe *p)
{
  char		**b;

  env->ret = EXIT_SUCCESS;
  if ((b = pars_param(tab, s->i, env)) == NULL)
    {
      env->ret = EXIT_FAILURE;
      s->failed = -1;
    }
  else if (is_builtin(b[0]))
    pipe_builtin(b, env, p, s);
  else
    {
      p->i = p->i + 1;
      do_fork(b, env, p);
      close(p->p[p->i % 2][0]);
    }
  env->ret = wait_process(s, p, 0);
}

void		do_process(char **tab, t_shell *env, t_command *s, t_pipe *p)
{
  int		t;
  char		**b;
  int		f;

  b = pars_param(tab, s->i, env);
  if ((t = fork()) == -1)
    return ;
  else if (t == 0)
    {
      if (b == NULL)
	exit(EXIT_FAILURE);
      if (dup2(p->p[p->i % 2][1], 1) == -1)
	exit(fprintf(stderr, "%s\n", strerror(errno)) * 0 + 1);
      if (!is_builtin(b[0]))
	close(p->p[p->i % 2][0]);
      if (p->i != 0 && !is_builtin(b[0]))
	if (dup2(p->p[p->i % 2 ? 0 : 1][0], 0) == -1)
	  exit(fprintf(stderr, "%s\n", strerror(errno)) * 0 + 1);
      f = minishell1(b, env);
      f == -1 ? exit(EXIT_FAILURE) : exit(EXIT_SUCCESS);
    }
  if (p->i > 0 && is_valide(b, env) && !is_builtin(b[0]))
    close(p->p[p->i % 2 ? 0 : 1][0]);
  close(p->p[p->i % 2][1]);
}

void		pipe_execution(char **tab, t_shell *env, t_command *s)
{
  t_pipe	p;

  p.i = 0;
  s->failed = 1;
  while (next_is_pipe(tab, s->i))
    {
      if (pipe(p.p[p.i % 2]) == -1)
        return ((void)fprintf(stderr, "%s\n", strerror(errno)));
      do_process(tab, env, s, &p);
      p.i = p.i + 1;
      s->i = s->i + length_param(tab, s->i);
    }
  s->failed = 1;
  dup2(s->save[1], 1);
  last_process(tab, env, s, &p);
  dup2(s->save[1], 1);
  dup2(s->save[0], 0);
  s->i = s->i + length_param(tab, s->i);
}
