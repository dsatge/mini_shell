#include "minishell.h"

void add_node(t_token *element, char *node_content)
{
	element->next = malloc(sizeof(t_token));
	if (element->next == NULL)
		return (ft_putstr_fd("Error malloc add_node", 2));
	element->next->str = ft_strdup(node_content);
	ft_token_type(node_content, element->next);
	element->next->next = NULL;
	return ;
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
	ft_token_type(argv[i], element);
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
	ft_print_list(head);
}