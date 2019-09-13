#include "sh_21.h"

/*
 * sh_traverse_command
 * This is the dispatcher of command (grammar) node
 * Just check what type of command we have and call the
 * right traverse.
*/
int	sh_traverse_command(t_ast_node *node, t_context *context)
{
	t_ast_node *child;
	int 		ret;

	ret = 0;
	child = node->children->content;
	if (child->symbol->id == sh_index(SIMPLE_COMMAND))
		ret = sh_traverse_simple_command(child, context);
	sh_env_update_ret_value_and_question(context->shell, ret);
	return (ret);
}