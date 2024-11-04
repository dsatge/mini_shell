#include "minishell.h"

void add_node(t_token *element, char *node_content)
{
	element->next = malloc(sizeof(t_token));
	if (element->next == NULL)
		return (ft_putstr_fd("Error malloc add_node", 2));
	element->next->str = ft_strdup(node_content);
	ft_token_type(element->next);
	element->next->next = NULL;
	return ;
}
void	ft_token_type(t_token *element)
{
	// int i;

	// i = 0;
	if (ft_ispipe(*element) == 0)
		element->type = pip;
	else if (ft_isredir(*element) == 0)
		element->type = redir;
	else
		element->type = word;
}

int	ft_checktype_order(t_token *element)
{
	element = element->next;
	if (element->type == pip)
		return (ft_putstr_fd("Error: 1st is pipe\n", 2), 1);
	while (element->next != NULL)
	{
		if (element->type == redir && element->next->type != word)
			return (ft_putstr_fd("Error: redir not followed by word\n", 2),1);
		if (element->type == pip && element->next->type == pip)
			return (ft_putstr_fd("Error: 2 pipes\n", 2),1);
		element = element->next;
	}
	if (element->type == pip || element->type == redir)
		return (ft_putstr_fd("Error: not ending by word\n", 2),1);
	return (0);
}

void	ft_tokenise(int argc, char **argv)
{
	t_token *element;
	t_token *head;
	int	i;

	i = 0;
	element = malloc(sizeof(t_token));
	if (element == NULL)
		return(ft_putstr_fd("Error malloc ft_tokenise", 2));
	element->str = ft_strdup(argv[i]);
	ft_token_type(element);
	element->next = NULL;
	i++;
	head = element;
	while (i < argc)
	{
		if(element->next != NULL)
			element = element->next;
		add_node(element, argv[i]);
		i++;
	}
	if (ft_checktype_order(head) == 1)
		return(ft_putstr_fd("Error argument order in ft_tokenise", 2));
	ft_print_list(head);
}
