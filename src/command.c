/*
 * In The Name Of God
 * ========================================
 * [] File Name : command
 *
 * [] Creation Date : 03-07-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "command.h"
#include "common.h"
#include "coordinator.h"

void send_command(const char *message, const char *user)
{
}

void quit_command(void)
{
	if (is_coordinator) {
		if (unlink("/tmp/coordinator") < 0)
			sdie("unlink()");
		printf("Coordinator died\n");
	}

	printf("Thank you for using the P2PChatroom\n");

	exit(0);
}

void command_dispatcher(const char *command)
{
	char verb[255];
	int len;

	len = sscanf(command, "%s", verb);
	if (len < 1)
		return;

	if (!strcmp(verb, "quit")) {
		quit_command();
	} else if (!strcmp(verb, "send")) {
		char user[255];
		char message[1024];

		len = sscanf(command, "%s %s: ", verb, user);
		if (len < 2) {
			printf("send user: message\n");
			return;
		}
		send_command(message, user);
	}
}
