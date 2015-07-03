/*
 * In The Name Of God
 * ========================================
 * [] File Name : main
 *
 * [] Creation Date : 02-07-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "common.h"
#include "coordinator.h"
#include "connections.h"

int is_coordinator = 0;

int main(int argc, char *argv[])
{
	int coordinator_fd;
	FILE *coordinator_file;

	coordinator_fd = open("/tmp/coordinator", O_EXCL | O_CREAT | O_WRONLY,
		0664);
	if (coordinator_fd > 0) {
		printf("New coordinator is selected\n");
		is_coordinator = 1;
		coordinator_file = fdopen(coordinator_fd, "w");
	}


	connections_run();

	if (is_coordinator) {
		if (unlink("/tmp/coordinator") < 0)
			sdie("unlink()");
		printf("Coordinator died");
	}

	return 0;
}