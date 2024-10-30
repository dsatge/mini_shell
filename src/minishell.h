#ifndef MINISHELL_H
    #define MINISHELL_H

# include "../lib/libft/libft.h"
# include "../lib/printf/ft_printf.h"
typedef enum s_type
{
    pip = 0,
    redir = 0,
    word = 0,
}   t_type;

typedef struct s_token
{
    char *str;
    t_type type;
    struct s_token *next;
}   s_token;

#endif