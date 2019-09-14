#include "sh_21.h"

/*
 * apply_expansion_to_children
 * We apply expansion here for all possible command (grammar) child.
 * simple_command, compound_command...
*/
static int	apply_expansion_to_children(t_ast_node *child, t_context *context)
{
	int 		ret;

	context->phase = E_TRAVERSE_PHASE_EXPANSIONS;
	if ((ret = sh_traverse_tools_browse(child, context)))
		return (ret);
	return (SUCCESS);
}

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
	if ((ret = apply_expansion_to_children(child, context)) != SUCCESS)
		return (ret);
	sh_traverse_tools_show_traverse_start(node, context);
	if (child->symbol->id == sh_index(SIMPLE_COMMAND))
		ret = sh_traverse_simple_command(child, context);
	sh_env_update_ret_value_and_question(context->shell, ret);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}