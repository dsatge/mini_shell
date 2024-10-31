#ifndef MINISHELL_H
    #define MINISHELL_H

# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"
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

//MAIN
void	ft_print_list(struct s_token *list);
//TOKENISE
void	add_node(t_token *element, char *node_content);
void	ft_token_type(t_token *element);
void	ft_tokenise(int argc, char **argv);
//TOKENISE_UTILS
int	    ft_ispipe(t_token element);
int     ft_isredir(t_token element);

#endif