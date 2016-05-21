/*
** exec_sh1.c for exec_sh1.c in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Sat May 21 16:32:56 2016 Melvin Personnier
** Last update Sat May 21 17:49:26 2016 Melvin Personnier
*/

#include "my.h"

static int	test_path(char **tab, char **env)
{
  int		i;
  char		*path_in_str;
  char		**path_in_array;
  char		*cmd;
  int		a;

  if ((path_in_str = get_var_env(env, "PATH=")) == NULL)
    {
      fprintf(stderr, "%s: Command not found.\n", tab[0]);
      return (-1);
    }
  path_in_array = my_str_to_wordtab_pattern(path_in_str, ":");
  i = -1;
  while (path_in_array[++i])
    {
      cmd = concat_str(path_in_array[i], tab[0], '/');
      if ((a = execve(cmd, tab, env)) != -1)
	return (a);
    }
  fprintf(stderr, "%s: Command not found.\n", tab[0]);
  return (-1);
}

static int	instant_exec(char **tab, char **env)
{
  int		a;

  a = execve(tab[0], tab, env);
  if (a == -1)
    fprintf(stderr, "%s: Command not found.\n", tab[0]);
  return (a);
}

int		exec_sh1(char **tab, char **env)
{
  if (tab[0][0] == '.' || tab[0][0] == '/')
    return (instant_exec(tab, env));
  test_path(tab, env);
  return (0);
}
