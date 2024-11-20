#ifndef MINISHELL_H
    #define MINISHELL_H
#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 10000
#endif

# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

enum e_quote_status
{
    DEFAULT,
    SINGLE_QUOTE,
    DOUBLE_QUOTE
};

typedef enum s_type
{
    pip,
    redir,
    word,
}   t_type;

typedef struct s_token
{
    char *str;
    t_type type;
    struct s_token *next;
}   t_token;

typedef struct s_command_list
{
    char    *str;
    struct s_command_list *next;    
}   t_command_list;


//MAIN
void	ft_print_list(struct s_token *list);
//LINE_TO_WORDS
int		ft_count_word(char *buffer);
void    ft_split_word(char *buffer, t_token *element);
//TOKENISE
void	add_node(t_token *element, char *node_content);
void	ft_token_type(t_token *element);
int		ft_checktype_order(t_token *element);
t_token	*ft_tokenise(char *buffer, int i, int len, t_token *element, int first_word);
void	ft_command_list(t_token *element);
//TOKENISE_UTILS
int		ft_ispipe(t_token element);
int		ft_isredir(t_token element);
char	*word_from_str(char *buffer, int start, int end);
void	free_all(t_token *list, char **tab);

#endif