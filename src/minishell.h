#ifndef MINISHELL_H
    #define MINISHELL_H
#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 10000
#endif

# define PROMPT "\001\e[0;102m\002=>\001\e[0m\e[0;95m\002Mini-merde>$ \001\e[0m\002"
// # define PROMPT ">"

# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int g_error_code;

typedef enum e_quote_status
{
	DEFAULT,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote;

typedef enum s_type
{
	pip,
	redir,
	word,
}	t_type;

typedef struct s_env
{
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	char *str;
	t_type type;
	struct s_token *next;
}	t_token;

typedef struct s_cmd
{
	char	**tab;
	t_type	type;
	bool	pipe_end;
}	t_cmd;

typedef struct s_pipe
{
	int		pipe_fd[2];
	int		abs_path;
	char	*file;
	char	**env;
	char	**path;
}	t_pipe;

// typedef struct	s_structlist
// {
// 	t_cmd	**head;
// 	t_cmd	**tail;
// 	int		list_len;
// }	t_structlist;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	struct s_list	*head;
	int				cmd_nbr;
	t_cmd			*cmd;
	// t_structlist	*key_p;
}	t_list;

typedef struct s_minish
{
	t_token			*element;
	t_type			*type;
	t_quote			*quote;
}	t_minish;


//MAIN
int				ft_buffer(char *buffer, t_token *token_list, t_minish *mini_struct);
//LINE_TO_WORDS_UTILS
bool			is_White_Space(char c);
bool			is_redir_pipe(char c);
char			*redir_pipe_to_word(char *buffer, int *i);
//LINE_TO_WORDS
char			*ft_quotes(char *buffer, int *i);
int				is_word(char *buffer, int *i, t_minish **mini_struct, int first_word);
char			*letters_to_word(char *word, char *buffer, int start, int i);
char			*ft_join_quotes(char *buffer, int *i, char *tmp);
t_token			*ft_split_word(char *buffer, t_minish *mini_struct);
//TOKENISE
int				ft_checktype_order(t_token *element);
t_token			*ft_tokenise_pipe_redir(char *word, t_minish *mini_struct, int first_word);
t_token			*ft_tokenise_word(char *word, t_minish *mini_struct, int first_word);
//TOKENISE_UTILS
void			ft_token_type(t_token *element);
int				ft_ispipe(t_token element);
int				ft_isredir(t_token element);
char			*word_from_str(char *buffer, int start, int end);
//SIGNAUX
void			signal_handle(void);
void			sigint_handle(int signal);
//FREE
void			free_list(t_token *list);
void			free_cmds(t_list *cmds);
void			free_tab(char **tab);
//LIST
int				cmds_list(t_token *list, t_list *cmds);
int				init_cmds_list(t_list *cmds, t_token *list, int next);
int				ft_cmd(t_token *list, t_list *cmds, int	nbr_cmd);
int				tab_cmds(t_token *list, t_list *cmds);
int	redir_cmds(t_token *list, t_list *cmds);
int	word_cmds(t_token *list, t_list *cmds);
//PRINT_TEST_LIST

// CAMMANDS
int				ft_builtin(t_list *cmds, t_pipe *pipex, t_env **ev);
void			ft_init_env(char **cmd, t_env **ev);
int				ft_echo(char **cmd);
int				ft_cd(char **cmd);
int				ft_pwd(char **cmd);
void			ft_env(t_env **ev);
void			ft_unset(char **cmd, t_env **ev);

//EXEC
void			init_pipex(t_list *cmds, t_pipe *pipex, char **env);
char			**add_path(char *add, int len, char **path_split);
int				init_path(char **env, t_pipe *pipex);
int				ft_exec(t_list *cmds, char **env, t_env **ev);
//EXEC_UTILS
void			one_exe(t_list *cmds, t_pipe *pipex);
void			first_exe(t_list *cmds, t_pipe *pipex);
void			next_exe(t_list *cmds, t_pipe *pipex);
void			last_exe(t_list *cmds, t_pipe *pipex);
int				invert_stdin(t_list *cmds, int fd);

#endif