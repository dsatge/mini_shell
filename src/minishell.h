/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:47:59 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/18 16:54:43 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# define PROMPT "\001\e[0m\e[0;95m\002>Mini-merde>$ \001\e[0m\002"
// # define PROMPT ">"

# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_quote_status
{
	DEFAULT,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}					t_quote;

typedef enum s_type
{
	pip,
	redir,
	word,
}					t_type;

typedef enum e_quote_type
{
	no_q,
	single_q,
	double_q,
}					t_quote_type;

typedef struct s_env
{
	char			*value;
	char			*type;
	struct s_env	*next;
}					t_env;

typedef struct s_env_head
{
	t_env			*head;
	unsigned int	size;
}					t_env_head;

typedef struct s_token
{
	char			*str;
	t_type			type;
	t_quote_type	quote_t;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			**tab;
	t_type			type;
	t_quote_type	quote_t;
}					t_cmd;

typedef struct s_o_cmd
{
	char			**tab;
	pid_t			pid;
	struct s_o_cmd	*next;
}					t_o_cmd;

typedef struct s_pipe
{
	int		pipe_fd[2];
	int		prev_pip;
	int		redir_in;
	int		redir_out;
	int		redir_pipe;
	int		fd;
	int		heredoc_pip[2];
	int		nbr_cmds;
	int		infile_fd;
	int		outfile_fd;
	int		abs_path;
	char	**path;
	char	**env;
}	t_pipe;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	struct s_list	*head;
	int				cmd_nbr;
	t_cmd			cmd;
}					t_list;

typedef struct s_minish
{
	t_token			*element;//free_list
	t_token			*element_head;
	t_token			*head_token;
	t_type			*type;//enum
	t_quote			*quote;//enum
	t_env_head		env;//ft_del existe
	t_pipe			*pipex;//env & path en char** A GERER
	t_list			*cmds;// free_cmds
	t_o_cmd			*o_cmd;
}					t_minish;

// int main(void)
// {
// 	t_minish data;

// 	avant loop:
// 	memset(&data, sizeof(t_minish), 0);
// 	apres loop:
// 	memset(&data.element, sizeof(t_minish), 0);
// 	memset(&data.tpye, sizeof(t_minish), 0);
// 	memset(&data.elem, sizeof(t_minish), 0);
// }


extern int			g_error_code;

// MAIN
int					ft_buffer(char *buffer,	t_token *token_list,
	t_minish *mini_struct);
// LINE_TO_WORDS_UTILS
bool				is_White_Space(char c);
bool				is_redir_pipe(char c, t_minish *minish);
char				*redir_pipe_to_word(char *buffer, int *i);
	// LINE_TO_WORDS
char				*ft_quotes(char *buffer, int *i);
int					is_word(char *buffer, int *i, t_minish **mini_struct,
						int first_word);
char				*letters_to_word(char *word, char *buffer, int start,
						int i);
char				*ft_join_quotes(char *buffer, int *i, char *tmp);
t_token				*ft_split_word(char *buffer, t_minish *mini_struct);
// TOKENISE
int					ft_checktype_order(t_token *element);
t_token				*ft_tokenise_pipe_redir(char *word, t_minish *mini_struct,
						int first_word, int quote_typ);
t_token				*ft_tokenise_word(char *word, t_minish *mini_struct,
						int first_word, int quote_typ);
// TOKENISE_UTILS
void				ft_token_type(t_token *element, int quote_typ);
int					ft_ispipe(t_token element);
int					ft_isredir(t_token element);
char				*word_from_str(char *buffer, int start, int end);
// SIGNAUX
void				signal_handle(void);
void				sigint_handle(int signal);
void				signal_child(void);
// FREE
void				free_list(t_token *list);
void				free_cmds(t_list *cmds);
void				free_env(t_env_head *env_head);
void				free_tab(char **tab);
void				free_all(t_minish *minish, bool clean_env);
// LIST
int					cmds_list(t_token *list, t_list *cmds);
int					init_cmds_list(t_list *cmds, t_token *list, int next);
int					ft_cmd(t_token *list, t_list *cmds, int nbr_cmd);
int					tab_cmds(t_token *list, t_list *cmds);
int					redir_cmds(t_token *list, t_list *cmds);
int					word_cmds(t_token *list, t_list *cmds);
int					pipe_cmds(t_token *list, t_list *cmds);
// PRINT_TEST_LIST

// COMMANDS
int				ft_builtin(t_env_head *env_head, t_minish *minish);
int				ft_init_env(char **env, t_env_head *env_head);
char			*get_value_env(char *cmd);
char			*get_type_env(char *cmd);
int				ft_echo(char **cmd);
int				ft_cd(char **cmd);
int				ft_pwd(char **cmd);
void			ft_env(t_env_head *env_head);
void			ft_unset(char **cmds, t_env_head *env_head);
int				ft_exit(t_env_head *env_head, t_minish *minish);
int				ft_export(char **cmd, t_env_head *env_head);
//EXEC
void			init_pipex(t_list *cmds, t_pipe *pipex, char **env);
void			ft_expand_args(t_list *cmds, t_env_head *env_head);
char			**add_path(char *add, int len, char **path_split);
int				init_path(char **env, t_pipe *pipex);
void			free_tab_2(char **tab, int size);
char			**buildtab(t_env_head *env_head);
int				ft_exec(t_list *cmds, t_env_head *env_head, t_minish *minish);
//EXEC_INIT
int				next_cmdexe(t_list **cmds, t_o_cmd **o_cmd, t_pipe *pipex);
int				exec_cmds(t_o_cmd **o_cmd, t_minish *minish, t_env_head *env_head);
//EXEC_ONLY_CMD
t_o_cmd			*ft_only_cmd(t_list *cmds);
//EXEC_UTILS
void			child_exe(t_list *cmds, t_minish *minish, t_o_cmd *o_cmd, t_env_head *env_head);
int				ft_redir(t_list **cmds, t_pipe **pipex, t_minish *minish);
int				ft_redir_in(t_list *list, t_pipe **pipex, t_minish *minish);
int				ft_redir_out(t_list *list, t_pipe **pipex);
//EXEC_REDIR
int				redir_in(t_pipe **pipex, t_list *list, t_minish *minish);
int				redir_out(t_pipe **pipex, t_list *list);
int 			redir_d_out(t_pipe **pipex, t_list *list);
int				redir_fdin(t_pipe **pipex, t_list *cmds, int prev_pip, t_env_head *env_head);
int				redir_fdout_pip(t_pipe **pipex);
int				redir_fdout(t_pipe **pipex, t_list *cmds);

// HEREDOC
int				heredoc(t_pipe **pipex, t_list *cmds, t_env_head *env_head, char *file_name);
char			*ft_expand_heredoc(char *buffer, t_env_head *env_head);
int				heredoc_check(t_minish *minish, t_env_head *env_head);
int	redir_heredoc(t_pipe **pipex, t_list *list);
// ERROR
int				error_special(char *buffer);
void			error_print_msg(char *str, t_env_head *env_head);
//EXPAND_UTILS
char			*expand_env_variable(char *res, const char *str, int *i, t_env_head *env_head);
char			*expand_exit_code(char *res, int *i);
//EXEC_INCHILD
int				ft_redir_manager(t_minish *minish, t_pipe *pipex, t_env_head *env_head, int pip);
//EXPORT_UTILS

void			print_declare(t_env **sorted);

//tests
void test_print_tab(char **tab);

#endif