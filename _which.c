#include "header.h"

/**
 * _is_path - Check if command is a path
 * @command: string
 * Return: 1 (Success) or 0 (Failure)
 */
int _is_path(char *command)
{
	return (*command == '/' || (*command == '.' && command[1] == '/'));
}

/**
 * _which - find in the path executable file.
 * @filename: filename to find in path.
 * @envp: array of environment variables.
 *
 * Return: path concatenated with filename.
 */
int _which(char *filename, char *envp[])
{
	char *path, *token, path_copy[BUFFER_SIZE], token_copy[BUFFER_SIZE];
	size_t i;
	/* input: ls */
	/* obtain path */

	token = NULL;
	path = _getenv(PATH, envp);
	if (!path) /*|| *path == '\0'*/
	{
		return (FALSE);
	}

	_str_copy(path_copy, path);
	/* split by :  and obtain token */
	for (i = 0; 1; i++)
	{
		token = strtok(((i == 0) ? path_copy : NULL), DELIM_PATH);
		if (token == NULL)
		{
			break;
		}

		_str_copy(token_copy, token);

		/* concatenate /bin(token) with /    */
		_str_concat(token_copy, "/");

		/* concatenate /bin/(token) with ls(filename) */
		_str_concat(token_copy, filename);
		/* validate token_copy can access to file with execute permission */

		/* if have access*/
		if (access(token_copy, F_OK | X_OK) != -1)
		{
			_str_copy(filename, token_copy);
			return (TRUE);
		}
	}
	return (FALSE);
}
