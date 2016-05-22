/*
** misc.c for misc in /home/riamon_v/rendu/PSU/couver-shell/minishell1
**
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
**
** Started on  Wed May 18 15:41:18 2016 vincent riamon
** Last update Sun May 22 18:48:30 2016 vincent riamon
*/

#include "my.h"

char		*concat_str(char *s1, char *s2, char c)
{
  char		*s3;
  int		i;
  int		j;
  int		len;

  i = -1;
  j = 0;
  len = ((s2 != NULL) ? strlen(s2) : 0);
  s3 = my_malloc(sizeof(char) * ((strlen(s1) + len) + 2));
  while (s1[++i])
    s3[i] = s1[i];
  s3[i++] = c;
  if (s2 != NULL)
    while (s2[j])
      s3[i++] = s2[j++];
  s3[i] = 0;
  return (s3);
}

char		*get_var_env(char **env, char *name)
{
  int		i;

  i = -1;
  while (env[++i] && strncmp(env[i], name, strlen(name)));
  if (!env[i])
    return (NULL);
  env[i][strlen(env[i])] = 0;
  return (env[i] + strlen(name));
}

char		**cpy_env(char **env)
{
  char		**tmp;
  int		i;

  tmp = my_malloc(sizeof(char *) * (tab_len(env) + 1));
  i = -1;
  while (env[++i])
    tmp[i] = strdup(env[i]);
  tmp[i] = NULL;
  return (tmp);
}

void	        aff_tab(char **tab)
{
  int		i;

  i = -1;
  while (tab[++i])
    printf("%s\n", tab[i]);
}
