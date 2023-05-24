#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define STDIN 0
#define BUFFER_SIZE 4096
/**
 * @brief Ansi characters to remove the ^C from the terminal
 * @note '\b' goes back one character
 * @note '\033[K' deletes from the current position to the end
 */
#define DEL_SIG "\b\b\033[K"
#define PROMPT "> "

// ---------------------------------------------------------
// Tools: Look down for the actual code :)

void	ft_bzero(char *buf)
{
	int i;

	i = 0;
	while (i < BUFFER_SIZE && buf[i] != '\0')
		buf[i++] = 0;
}

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(int fd, char *str)
{
	if (str == NULL)
		return ;
	write(fd, str, ft_strlen(str));
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

// ---------------------------------------------------------
/**
 * @brief Signal handler for SIGINT (Ctrl + C)
 * @note This handler is used when entering commands.
 * @note It may be better to use rl_on_new_line, rl_replace_line and rl_redisplay functions. More research is needed.
 * 
 * @param sig 
 */
void	termSigHandler(int sig)
{
	sig++; // ? this will be handled in the future, where more signals are handled in the same function
	ft_putstr_fd(0, DEL_SIG "\n" PROMPT);
}

void	parentSigHandler(int sig)
{
	sig++;
	ft_putstr_fd(0, DEL_SIG); // Delete the "^C" from the terminal
}

pid_t	childExec(int child_nbr)
{
	pid_t pid = fork();
	if (pid > 0) // parent
		return pid;
	else if (pid < 0)
	{
		printf("Error: fork() failed\n");
		exit(1);
	}
	else
	{
		int i;
		signal(SIGINT, SIG_DFL); // Use the default handler
		while (1)
		{
			i = 0;
			while (i < 2000000000)
				i++;
			printf("Child %d is still alive (end it with Ctrl + C)\n", child_nbr);
		}
	}
	return (-1); // This should never happen
}

void	show_status(int child_nbr, int status)
{
	if (WIFEXITED(status)) {
		int exit_status = WEXITSTATUS(status);
		printf("Child %d process exited with status code: %d\n", child_nbr, exit_status);
		if (exit_status != 0) {
			printf("Error: %s\n", strerror(exit_status)); // Display error message
		}
	} else if (WIFSIGNALED(status)) {
		int s = WTERMSIG(status);
		printf("Child %d process terminated by signal\n", child_nbr);
		printf("  Signal: %d -> %s\n", s, strsignal(s));
	}
}

void	execute(char *buf)
{
	if (ft_strlen(buf) - 1 == 0)
		return ;
	printf("Executing: %s    (len: %d)\n", buf, ft_strlen(buf));

	pid_t pid1 = childExec(1);
	pid_t pid2 = childExec(2);
	int status;
	printf("Parent waiting for childs to finish\n");
	printf("pid1: %d, pid2: %d\n", pid1, pid2);
	waitpid(pid1, &status, 0);
	show_status(1, status);
	waitpid(pid2, &status, 0);
	show_status(2, status);
	printf("Parent finished waiting\n");
}


int	main(void)
{
	char buf[BUFFER_SIZE];

	signal(SIGINT, termSigHandler); // Ctrl + C
	//signal(SIGTERM, ); // Ctrl + D
	//signal(SIGQUIT, ); // Ctrl + \ (quit)
	while (1)
	{
		ft_bzero(buf);
		ft_putstr_fd(1, PROMPT);
		read(STDIN, buf, BUFFER_SIZE);
		signal(SIGINT, parentSigHandler); // Ctrl + C
		// signal(SIGINT, SIG_IGN); // Ignore the signal
		if (ft_strcmp(buf, "exit") == 0)
			break;
		execute(buf);
		signal(SIGINT, termSigHandler); // Ctrl + C
	}
	printf("Exiting minishell\n");
	return (0);
}
