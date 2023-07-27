#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 64
#define MAX_ARG_LENGTH 256

typedef struct
{
	char *args[MAX_ARGS];
	int tokCount;
	char *nextCommand;
} param_t;

/**
 * free_args - free argumment
 */

void free_args(param_t *params)
{
	int i;

	for (i = 0; i < params->tokCount; i++)
	{
		free(params->args[i]);
		params->args[i] = NULL;
	}
params->tokCount = 0;
}

int process_string(param_t *params)
{
	char *nextArg;
	int argCount = 0;

	nextArg = strtok(params->nextCommand, " \t\r\n\a");
	while (nextArg != NULL)
	{
		if (argCount >= MAX_ARGS)
		{
			fprintf(stderr, "Error: Too many arguments in command.\n");
			free_args(params);
			return (0);
		}

	params->args[argCount] = malloc(strlen(nextArg) + 1);
	if (params->args[argCount] == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed.\n");
		free_args(params);
		return (0);
	}

	strcpy(params->args[argCount], nextArg);
	argCount++;

	nextArg = strtok(NULL, " \t\r\n\a");
	}

	params->tokCount = argCount;
	return (argCount);
}
int shell_main(void)
{
	int argCount;
	param_t params;
	char command[] = "ls -l -a /path/to/directory";
	int i;

	for (i = 0; i < MAX_ARGS; i++)
	{
		params.args[i] = NULL;
	}
	params.nextCommand = command;
	params.tokCount = 0;

	argCount = process_string(&params);
	if (argCount > 0)
	{
		printf("Command arguments:\n");
		for (i = 0; i < argCount; i++)
		{
			printf("%d: %s\n", i, params.args[i]);
		}
	}
	free_args(&params);
	return (0);
}
