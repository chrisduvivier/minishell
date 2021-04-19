#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

pid_t Fork(void)
{
    pid_t pid;

    if ((pid = fork()) < 0)
        unix_error("Fork error");
    return pid;
}

int main()
{
	int status;
	pid_t pid;
	printf("Hello\n");
	pid = Fork();
	printf("%d\n", !pid);
	if (pid != 0)
	{
		if (waitpid(-1, &status, 0) > 0)
		{
			if (WIFEXITED(status) != 0)
				printf("%d\n", WEXITSTATUS(status));
		}
	}
	printf("Bye\n");
	exit(2);
}