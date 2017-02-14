#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	pid_t pid;
	if (pid = fork()) {
		printf("parent (%i) here. child-pid: %i.\n", getpid(), pid);
		// we are not waiting for children here...
		sleep(20); // time to watch the zombie
	} else {
		printf("child here. pid: %i.\n", getpid());
		sleep(2);
		// terminates before the parent, turns into zombie
	}

	printf("%i terminating.\n", getpid());
	return 0;
}
