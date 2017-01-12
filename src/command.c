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
#include "message.h"
#include "peer.h"
#include "net.h"
#include "info.h"

void send_command(char *message, const char *user)
{
	struct message m;
	struct peer *p;
	int i;

	m.body = message;
	m.m_size = strlen(message);
	strcpy(m.dst_name, user);
	strcpy(m.src_name, info_username);


	for (i = 0; i < peer_list_size(); i++) {
		p = peer_list_get(i);
		if (!strcmp(p->name, user)) {
			send_message(&m, p->socket);
			return;
		}
	}
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

		len = sscanf(command, "%s %s %s", verb, user, message);
		if (len < 3) {
			printf("send user: message\n");
			return;
		}
		send_command(message, user);
	}
}
