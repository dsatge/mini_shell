#include "minishell.h"

void	ft_token_type(t_token *element)
{
	if (ft_ispipe(*element) == 0)
		element->type = pip;
	else if (ft_isredir(*element) == 0)
		element->type = redir;
	else
		element->type = word;
}

int	ft_checktype_order(t_token *element)
{
	// if(element->next == NULL || element == NULL)
	// 	return(ft_putstr_fd("Error: A REVOIR\n", 2), 1);
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
// free_token(t_token *lst)
// {

// }

t_token	*ft_tokenise(char *buffer, int i, int len, t_token *element, int first_word)
{
	t_token	*new_node;

	if (first_word == 0)
	{
		element->str = word_from_str(buffer, i, len);
		ft_token_type(element);
		element->next = NULL;
	}
	else
	{
		while (element->next)
			element = element->next;
		new_node = malloc(sizeof(t_token));
		if (!new_node)
			return (ft_putstr_fd("Error malloc add_node\n", 2), NULL);
		new_node->next = NULL;
		new_node->str = word_from_str(buffer, i, len);
		ft_token_type(new_node);
		// if (element->next == NULL) // || element->next->str == NULL)
		element->next = new_node;
		element= element->next;
	}
	return (element);
}

void add_cmd_node(t_command_list *element, char *node_content)
{
	element->next = malloc(sizeof(t_command_list));
	if (element->next == NULL)
		return (ft_putstr_fd("Error malloc add_cmd_node\n", 2));
	element->next->str = ft_strdup(node_content);
	element->next->next = NULL;
	return ;
}
void	ft_print_cmdlist(struct s_command_list *cmd_list)
{
	int i;
	
	i = 0;
	ft_printf("command list:\n");
	while (cmd_list != NULL)
	{
		ft_printf("list[%i] = %s\n", i, cmd_list->str);
		i++;
		cmd_list = cmd_list->next;
	}
	return ;
}
t_command_list	ft_cmd_list(struct s_command_list *cmd_list, s_token *element)
{
	
}
)

// void	ft_command_list(t_token *element)
// {
// 	t_command_list	*cmd;
// 	t_command_list	*head;
// 	char			*cmd_content;
// 	char			*tmp;

// 	cmd = malloc(sizeof(t_command_list));
// 	if (!cmd)
// 		return (ft_putstr_fd("Error malloc ft_command_list\n", 2));
// 	cmd->next = NULL;
// 	head = cmd;
// 	while (element != NULL)
// 	{
// 		cmd_content = ft_strdup("");
// 		while (element->type != pip && element->next != NULL)
// 		{
// 			tmp = cmd_content;
// 			cmd_content = ft_strjoin(cmd_content, " ");
// 			// free(tmp);
// 			tmp = cmd_content;
// 			cmd_content = ft_strjoin(cmd_content, element->str);
// 			free(tmp);
// 			element = element->next;
// 		}
// 		if (element->next == NULL)
// 		{
// 			tmp = cmd_content;
// 			cmd_content = ft_strjoin(cmd_content, " ");
// 			// free(tmp);
// 			tmp = cmd_content;
// 			cmd_content = ft_strjoin(cmd_content, element->str);
// 			free(tmp);
// 		}
// 		add_cmd_node(cmd, cmd_content);
// 		cmd = cmd->next;
// 		element = element->next;
// 	}
// 	ft_print_cmdlist(head->next);
// 	free_all(element, NULL); // temporaire A ENLEVER PLUS TARD
// }
