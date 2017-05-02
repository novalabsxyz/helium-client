#ifndef TEST_CLIENT_INTERFACE_atom_api
#define TEST_CLIENT_INTERFACE_atom_api

#include "atom_api.h"
#include "atom_api_message.h"

#define MESSAGE_HEADER_T struct message_header_atom_api
#define MESSAGE_T struct message_atom_api
#define MESSAGE_OVERHEAD MESSAGE_OVERHEAD_atom_api
#define MESSAGE_MAX_SIZE MESSAGE_MAX_SIZE_atom_api

#define DECODE_HEADER decode_message_header_atom_api

#define DECODE_MESSAGE decode_message_atom_api
#define ENCODE_MESSAGE encode_message_atom_api

#endif /* TEST_CLIENT_INTERFACE_atom_api */
