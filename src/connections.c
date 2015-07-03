/*
 * In The Name Of God
 * ========================================
 * [] File Name : connections
 *
 * [] Creation Date : 02-07-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/
#include "connections.h"
#include "coordinator.h"
#include "peer.h"

#include <stdio.h>

void connections_run(void)
{
	FILE *peers_file;
	int peer_port, peer_status;

	if (is_coordinator)
		peers_file = fopen("/temp/peers", "r+");
	else
		peers_file = fopen("/temp/peers", "w");

	while (fscanf(peers_file, "%d %d", &peer_port, &peer_status) < 2) {
		struct peer *new = peer_new(peer_port, peer_status);
		peer_list_add(new);
	}
	if (is_coordinator) {
		fprintf(peers_file, "%d %d\n", 1373, 1);
	}
}
