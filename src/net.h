#ifndef NET_H
#define NET_H

int send_message(const struct message *message, int socket_fd);

int recv_message(struct message *message, int socket_fd);

#endif
