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
#include <stdlib.h>
#include <stdint.h>

#include "peer.h"

static struct peer *head;
static int size;

struct peer *peer_new(uint16_t port, int status)
{
	struct peer *new;
	
	new = malloc(sizeof(struct peer));
	new->name[0] = 0;
	new->port = port;
	new->status = status;
	new->next = NULL;

	return new;
}


void peer_list_add(struct peer *obj)
{
	if (!head) {
		head = obj;
		size++;
		return;
	}

	struct peer *it = head;

	while (it->next) {
		it = it->next;
	}
	it->next = obj;

	size++;

	return;
}

int peer_list_size(void)
{
	return size;
}

struct peer *peer_list_get(int index)
{
	int i = 0;
	struct peer *it = head;

	while (it) {
		if (i == index)
			return it;
		it = it->next;
		i++;
	}

	return NULL;
}
