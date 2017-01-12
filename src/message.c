#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "message.h"

int message_serialize(FILE *dest, const struct message *message)
{
	int return_value;
	
	if (message->m_size != 0) {
		return_value = fprintf(dest, "%s %s %zu\n%s",
				message->src_name, message->dst_name,
				message->m_size, message->body);
	} else {
		return_value = fprintf(dest, "%s %s %zu\n",
				message->src_name, message->dst_name,
				message->m_size);
	}
	
	if (return_value < 0)
		sdie("message_serialize printf()");

	fflush(dest);
	return return_value;
}

int message_deserialize(FILE *src, struct message *message)
{
	int return_value = 0;

	if (fscanf(src, "%s", message->src_name) != 1)
		return -1;
	return_value += strlen(message->src_name);

	if (fscanf(src, "%s", message->dst_name) != 1)
		return -1;
	return_value += strlen(message->dst_name);

	if (fscanf(src, "%zu", &message->m_size) != 1)
		return -1;

	message->body = calloc(message->m_size + 1, sizeof(char));

	/* Read message body start indicator ('\n') */
	fgetc(src);
	return_value += fread(message->body, message->m_size,
		sizeof(char), src);

	return return_value;
}
