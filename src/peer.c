/*
 * In The Name Of God
 * ========================================
 * [] File Name : peer
 *
 * [] Creation Date : 02-07-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/
#include "peer.h"

#include <stdlib.h>

static struct peer *head;

struct peer *peer_new(int port, int status)
{
	struct peer *new = malloc(sizeof(struct peer));
	new->port = port;
	new->status = status;
	new->next = NULL;
}


void peer_list_add(struct peer *obj)
{
	if (!head) {
		head = obj;
		return;
	}

	struct peer *it = head;

	while (it->next) {
		it = it->next;
	}
	it->next = obj;

}

int peer_list_size(void)
{
	int index = 0;
	struct peer *it = head;

	while (it) {
		it = it->next;
		index++;
	}

	return index;
}

struct peer *peer_list_get(int index)
{
}

