#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/prctl.h>

int main(int argc, char **argv)
{
	pid_t pid, pid2;

	// grand-parent to be a subreaper,
	// causing it to become the adopter instead of pid=1
	// (this does not fork-inherit)
	prctl(PR_SET_CHILD_SUBREAPER, 1L, 0L, 0L, 0L);

	// create child and grand-child,
	// let the grand-child terminate and be adopted by reaper
	if (pid = fork()) {
		printf("grand-parent (%i) here. child-pid: %i.\n", getpid(), pid);
		sleep(15);
	} else {
		printf("parent here. pid: %i. \n", getpid());
		if (pid2 = fork()) {
			sleep(1);
			printf("parent here (%i). just forked again. child: %i.\n",
					getpid(), pid2);
			sleep(1);
		} else {
			printf("(grand)-child here: %i\n", getpid());
			// will be adopted by grand-parent
			sleep(25);
		}
	}

	printf("%i terminating.\n", getpid());
	return 0;
}
