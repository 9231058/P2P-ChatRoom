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
#ifndef PEER_H
#define PEER_H

struct peer {
	int socket_fd;
	int port;
	int status;
	struct peer *next;
};


struct peer *peer_new(int port, int status);

void peer_list_add(struct peer *obj);

int peer_list_size(void);

struct peer *peer_list_get(int index);

#endif
