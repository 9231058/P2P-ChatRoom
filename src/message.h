#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>

/*
 * message header fields must be separate with ' ', and
 * connection created over TCP so field sequence is important.
 * after message header there is just ONE '\n' and then message
 * body come.
 *
 * @source_name
 *
 * @sink_name
 *
 * @size: sizeof message body in bytes
 *
 * +-------------+------------------+
 * | source_name | destination_name |
 * +-------------+------------------+
 * |                                |
 * |         Message Body           |
 * |                                |
 * +--------------------------------+
*/

struct message {
	char src_name[255];
	char dst_name[255];
	size_t m_size;
	char *body;
};

int message_serialize(FILE *dst, const struct message *message);

int message_deserialize(FILE *src, struct message *message);

#endif
