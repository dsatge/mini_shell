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





void	add_node(t_token *element, char *node_content);
void	ft_tokenise(int argc, char **argv);



#endif