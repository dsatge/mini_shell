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
# include <errno.h>
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
	char				*name;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	char *str;
	t_type type;
	struct s_token *next;
}	t_token;

typedef struct s_command_list
{
	struct s_token	*element;
	struct s_command_list *next_cmd;    
}	t_command_list;

typedef struct s_dir_list
{
	struct s_token	*element;
	struct s_dir_list *next_dir;
}	t_dir_list;

typedef struct s_minish
{
	t_command_list	*cmd;
	t_token			*element;
	t_type			*type;
	t_quote			*quote;
}	t_minish;


//MAIN
t_command_list	*ft_print_cmdlist(struct s_command_list *cmd_list);
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
t_command_list	*ft_cmd_list(t_minish *mini_struct, t_token *element);
// t_command_list	*add_cmd_node(t_command_list *element, t_token *list_node);
//TOKENISE_UTILS
void			ft_token_type(t_token *element);
int				ft_ispipe(t_token element);
int				ft_isredir(t_token element);
char			*word_from_str(char *buffer, int start, int end);
t_command_list	*init_list(char *buffer, t_minish *minish, t_command_list *cmd_list, t_token *tok_list);
//SIGNAUX
void			signal_handle(void);
void			sigint_handle(int signal);
//FREE
void			free_list(t_token *list);
void			free_dir(struct s_dir_list *dir_list);
void			free_all(t_token *list, t_minish *mini_struct);
void			free_cmd(struct s_command_list *cmd_list);
void			free_uplevel(int level, t_minish *minish, t_token *toklist, t_command_list *cmdlist, char *buff);
// void	free_all(t_token *list, char **tab);
//DIR_LIST
t_dir_list		*ft_dir_list(t_minish *mini_struct, t_token *token_list);
//PRINT_TEST_LIST
t_command_list	*ft_print_cmdlist(struct s_command_list *cmd_list);
t_dir_list	*ft_print_dirlist(struct s_dir_list *dir_list);

// CAMMANDS

int	ft_builtin(t_token *cmd);
int ft_unset(t_token *cmd);
int ft_echo(t_token *cmd);
int ft_pwd(t_token *cmd);
int	ft_cd(t_token *cmd);

#endif