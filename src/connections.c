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
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "connections.h"
#include "coordinator.h"
#include "peer.h"
#include "common.h"
#include "message.h"
#include "net.h"
#include "info.h"

int connection_is_run = 1;

void *connections_run(void *data)
{

	FILE *peer_file;
	int peer_port, peer_status;
	char peer_name[255];

	if (is_coordinator) {
		peer_file = fopen("/tmp/peers", "w");
	} else {
		peer_file = fopen("/tmp/peers", "r");
	}

	if (!peer_file)
		sdie("peer_file fopen()");

	int server_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_addr;
	socklen_t server_addr_len = sizeof(server_addr);

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(0);

	if (bind(server_socket, (const struct sockaddr *) &server_addr,
				server_addr_len) == -1)
		sdie("bind()");
	getsockname(server_socket, (struct sockaddr *) &server_addr,
			&server_addr_len);
	if (listen(server_socket, 10) == -1)
		sdie("listen()");

	if (is_coordinator) {
		fprintf(peer_file, "%s %hu %d\n", info_username, ntohs(server_addr.sin_port), 1);
		fflush(peer_file);
	}

	while (fscanf(peer_file, "%s %d %d", peer_name, &peer_port, &peer_status) == 3) {
		struct peer *new = peer_new(peer_port, peer_status);
		strcpy(new->name, peer_name);

		if (peer_status) {
			struct message m;
			char m_port[255];
			int client_socket;
			struct sockaddr_in client_addr;

			client_socket = socket(AF_INET, SOCK_STREAM, 0);

			socklen_t client_addr_len = sizeof(client_addr);

			client_addr.sin_family = AF_INET;
			client_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
			client_addr.sin_port = htons(peer_port);

			connect(client_socket,
					(const struct sockaddr *) &client_addr,
					client_addr_len);
			new->socket = client_socket;

			sprintf(m_port, "%hu", ntohs(server_addr.sin_port));
			m.m_size = strlen(m_port);
			m.body = m_port;
			strcpy(m.src_name, info_username);
			strcpy(m.dst_name, new->name);
			send_message(&m, client_socket);
		}

		peer_list_add(new);
	}

	while (connection_is_run) {
		int i = 0;
		int max_socket_fd;
		fd_set socket_fds_set;

		FD_ZERO(&socket_fds_set);
		FD_SET(server_socket, &socket_fds_set);

		max_socket_fd = server_socket;

		for (i = 0; i < peer_list_size(); i++) {
			int s;

			s = peer_list_get(i)->socket;
			max_socket_fd = (s > max_socket_fd) ? s : max_socket_fd;
			FD_SET(s, &socket_fds_set);
		}

		if (select(max_socket_fd + 1, &socket_fds_set,
					NULL, NULL, NULL) < 0)
			sdie("select");

		if (FD_ISSET(server_socket, &socket_fds_set)) {
			struct sockaddr_in client_addr;
			socklen_t client_addr_len;

			client_addr_len = sizeof(client_addr);

			int client_socket = accept(server_socket,
					(struct sockaddr *) &client_addr,
					&client_addr_len);

			struct peer *new = peer_new(0, 1);
			new->socket = client_socket;
			peer_list_add(new);
		}
		for (i = 0; i < peer_list_size(); i++) {
			struct peer *p;

			p = peer_list_get(i);
			if (FD_ISSET(p->socket, &socket_fds_set)) {
				struct message m;

				if (recv_message(&m, p->socket) <= 0) {
					fflush(stdout);
					printf("\nP2PChatroom %s left us alone\n", p->name);
					close(p->socket);
					peer_list_delete(i);
					i--;
				} else {
					if (strlen(p->name) == 0) {
						strcpy(p->name, m.src_name);
						sscanf(m.body, "%hu", &p->port);
						if (is_coordinator) {
							fprintf(peer_file, "%s %hu %d\n", p->name, p->port, p->status);
							fflush(peer_file);
						}
					} else {
						fflush(stdout);
						printf("\nP2PChatroom %s: %s\n", m.src_name, m.body);
					}
				}
			}
		}

	}
	return NULL;
}
