#include <stdio.h>

#include "message.h"
#include "net.h"
#include "common.h"

int send_message(const struct message *message, int socket_fd)
{
	FILE *socket_file = fdopen(socket_fd, "r+");

	if (socket_file == NULL)
		slog("fdopen()");

	return message_serialize(socket_file, message);
}

int recv_message(struct message *message, int socket_fd)
{
	FILE *socket_file = fdopen(socket_fd, "r+");

	if (socket_file == NULL)
		slog("fdopen()");

	return message_deserialize(socket_file, message);
}
