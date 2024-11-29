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
		return (ft_putstr_fd("Error: 1st is pipe\n", 2), -1);
	while (element->next != NULL)
	{
		if (element->type == redir && element->next->type != word)
			return (ft_putstr_fd("Error: redir not followed by word\n", 2), -1);
		if (element->type == pip && element->next->type == pip)
			return (ft_putstr_fd("Error: 2 pipes\n", 2),1);
		element = element->next;
	}
	if (element->type == pip || element->type == redir)
		return (ft_putstr_fd("Error: not ending by word\n", 2), -1);
	return (0);
}

t_token	*ft_tokenise(char *buffer, int i, int len, t_minish *mini_struct, int first_word)
{
	t_token	*new_node;

	if (first_word == 0)
	{
		mini_struct->element->str = word_from_str(buffer, i, len);
		ft_token_type(mini_struct->element);
		mini_struct->element->next = NULL;
	}
	else
	{
		while (mini_struct->element->next)
			mini_struct->element = mini_struct->element->next;
		new_node = malloc(sizeof(t_token));
		if (!new_node)
			return (ft_putstr_fd("Error malloc add_node\n", 2), NULL);
		new_node->next = NULL;
		new_node->str = word_from_str(buffer, i, len);
		if (!new_node->str)
			return (NULL);
		ft_token_type(new_node);
		// if (element->next == NULL) // || element->next->str == NULL)
		mini_struct->element->next = new_node;
		mini_struct->element= mini_struct->element->next;
	}
	return (mini_struct->element);
}

t_command_list	*ft_cmd_list(t_minish *mini_struct, t_token *token_list)
{
	t_command_list	*cmd_list;
	t_command_list	*head;

	(void)mini_struct;
	cmd_list = NULL;
	head = NULL;
	if (!token_list)
		return (ft_putstr_fd("Error no element in ft_cmd_list\n", 2), NULL);
	while (token_list)
	{
		cmd_list = add_cmd_node(cmd_list, token_list);
		if (head == NULL)
		{
			head = cmd_list;
			// printf("head = %p cmd_list = %p element = %s\n", head, cmd_list, element->str);
			// printf("CHECK : %s\n", cmd_list->element->str);
		}
		while (token_list->next && token_list->type != pip)
		{
			token_list = token_list->next;
		}
		if (!token_list->next)
			break;	
		token_list = token_list->next;
	}
	// printf("head = %p cmd_list = %p head 1st = %s\n", head, cmd_list, head->element->str);
	// printf("test = %s\n", element->str);
	return (head);
}

t_command_list	*add_cmd_node(t_command_list *cmd_list, t_token *token_list)
{
	t_command_list	*new_node;

	// printf("element = %s\n", list_node->str);
	if (!token_list)
		return (NULL);
	while (cmd_list && cmd_list->next_cmd)
		cmd_list = cmd_list->next_cmd;
	new_node = malloc(sizeof(t_command_list));
	if (!new_node)
		return (ft_putstr_fd("Error malloc add_cmd_node\n", 2), NULL);
	// element->next->str = ft_strdup(node_content);
	new_node->element = token_list;
	new_node->next_cmd = NULL;
	if (cmd_list)
		cmd_list->next_cmd = new_node;
	return (new_node);
}

// t_command_list	ft_cmd_list(struct s_command_list *cmd_list, t_token *element)
// {
	
// }

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
