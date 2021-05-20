#ifndef VISITOR_H
# define VISITOR_H

# include <stdio.h>
# include "ast.h"

void	visitor_visit_nodes(t_ast *node);
void	visitor_visit_root(t_ast *node);
void	visitor_visit_redirect(t_ast *node);
void	visitor_visit_pipe(t_ast *node);
void	visitor_visit_simplecommand(t_ast *node);
char	*print_node_type(int type);

#endif /* ifndef VISITOR_H */
