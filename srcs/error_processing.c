#include "includes/env.h"
#include "includes/types.h"
#include "history/history.h"
#include "includes/errors.h"
#include "includes/exit_status.h"

static void	param_free(t_env_list *env, t_data_processing *g_data_processing)
{
	t_env_list	*tmp;

	tmp = NULL;
	while (env != NULL)
	{
		tmp = env;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp->next;
	}
	// g_data_processing = NULL;
	clear_history(&g_data_processing->start_history);
}

static void	execution_exit(t_env_list *env,
		t_data_processing *g_data_processing)
{
	param_free(env, g_data_processing);
	exit(OK);
}

void	error_processing(t_env_list *env,
		t_data_processing *g_data_processing, int error_code)
{
	if (error_code != OUT
		&& error_code != ERROR_BAD_COMMAND
		&& error_code != ERROR_PARSER
		&& error_code != ERROR_EXIT_ARGC)
	{
		if (error_code == ERROR_EXIT && g_data_processing->ex_st == OK)
		{
			execution_exit(env, g_data_processing);
		}
		param_free(env, g_data_processing);
		exit(g_data_processing->ex_st);
	}
}
