/*
** signals.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 18:13:27 2016
** Last update Sat Jun  4 13:47:44 2016 Bertrand Buffat
*/

#include "shell.h"

bool	flag_ctrlc = 0;
bool	flag_window = 0;
bool	flag_stop = 0;

void	resize_win(t_shell *sh)
{
  char	*term;

  if ((term = get_var_env(sh->env, "TERM=")))
    setupterm(term, 1, (int *)0);
  else
    setupterm("xterm", 1, (int *)0);
  sh->prompt->nbcols = tigetnum("cols");
  sh->prompt->nblines = tigetnum("lines");
  erase_down_lines(sh->prompt, sh->prompt->nblines);
  aff_prompt(sh->prompt);
  flag_window = 0;

}

void	check_signals(t_shell *sh)
{
  if (flag_ctrlc)
    {
      memcpy(sh->prompt->line + sh->prompt->count_char, "^C", 2);
      sh->prompt->count_char += 2;
      clean_screen(sh->prompt);
      update_prompt(sh->prompt);
      aff_prompt(sh->prompt);
      flag_ctrlc = 0;
      --sh->prompt->nbr;
    }
  if (flag_window)
    resize_win(sh);
  if (flag_stop)
    {
      write(1, "\n[1]+ Stopped\t\t./42sh\n", 24);
      update_prompt(sh->prompt);
      flag_stop = 0;
    }
}

void			handler(int sig)
{
  if (sig == SIGINT)
    flag_ctrlc = 1;
  if (sig == SIGWINCH)
    flag_window = 1;
  if (sig == SIGSTOP)
    flag_stop = 1;
}

void	signal_handler(void)
{
  signal(SIGINT, handler);
  signal(SIGWINCH, handler);
  signal(SIGTSTP, handler);
}
