/*
** get_std_input.c for  in /home/buffat_b/couver-shell/src
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Sun May 29 04:12:22 2016
** Last update Sun May 29 04:20:21 2016 
*/

#include "shell.h"

char	*one_function_get_line(char *old_line, int turn, int old_size)
{
  char	buffer[1024];
  char	*line;
  int	new_size;

  if (!(line = malloc(sizeof(char) * (turn * 1024))))
    return (NULL);
  if (old_line)
    {
      memcpy(line, old_line, old_size);
      free(old_line);
    }
  if (!(new_size = read(0, buffer, 1024)))
    {
      line[old_size] = 0;
      return (line);
    }
  memcpy(line + old_size, buffer, new_size);
  return (one_function_get_line(line, ++turn, new_size + old_size));
}

void	get_std_input(t_shell *sh)
{
  char	**cmd;
  char	**instr;
  char	*line;
  int	i;

  if (!(line = one_function_get_line(NULL, 1, 0))
      || !(instr = my_str_to_wordtab_pattern(line, "\n")))
    return ;
  i = -1;
  while (instr[++i])
    {
      //temporary minishell
      cmd = lexer(instr[i]);
      update_history(cmd, sh);
      if (!check_command(cmd))
	the_execution(cmd, sh);
      //end
    }
  free(line);
  free_tab(instr);
}