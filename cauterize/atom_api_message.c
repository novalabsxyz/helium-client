#include "atom_api_message.h"

#define R enum caut_status
#define EI struct caut_encode_iter
#define DI struct caut_decode_iter
#define FSET(FS,IX) ((FS) & (1ull << (IX)))

/* type descriptors */
const caut_type_descriptors_atom_api_t type_descriptors = {
  {
    .name = "res_send",
    .hash = { 0xCF,0x96,0xCE,0x11,0xBB,0x83,0xA8,0x24,0x20,0x01,0x85,0x88,0x3B,0x24,0x73,0x30,0xC7,0xEC,0xDF,0x06 },
    .encode = (gen_encode*)encode_res_send,
    .decode = (gen_decode*)decode_res_send,
    .min_size = 1,
    .max_size = 1,
  },
  {
    .name = "res_info",
    .hash = { 0x91,0xAA,0x13,0x22,0x01,0x0C,0xA6,0xF3,0x75,0x6D,0x0A,0xAA,0x2D,0x19,0x8E,0xB2,0xDE,0xA5,0x50,0xDC },
    .encode = (gen_encode*)encode_res_info,
    .decode = (gen_decode*)decode_res_info,
    .min_size = 21,
    .max_size = 21,
  },
  {
    .name = "res_connect",
    .hash = { 0x36,0xB7,0xEE,0x9E,0xD1,0x64,0xE0,0x5C,0xF4,0x73,0xAB,0x37,0x40,0x16,0x1B,0x0F,0x26,0x90,0xF7,0x87 },
    .encode = (gen_encode*)encode_res_connect,
    .decode = (gen_decode*)decode_res_connect,
    .min_size = 1,
    .max_size = 1,
  },
  {
    .name = "frame_app",
    .hash = { 0x98,0x0A,0x97,0x15,0x1E,0x6B,0x90,0xB3,0xF6,0xD4,0x1E,0x6C,0x55,0xAC,0x92,0x88,0x9C,0x16,0xA1,0x79 },
    .encode = (gen_encode*)encode_frame_app,
    .decode = (gen_decode*)decode_frame_app,
    .min_size = 1,
    .max_size = 1,
  },
  {
    .name = "poll_frame",
    .hash = { 0x59,0x25,0xF7,0x25,0xFE,0x35,0xA8,0x75,0x6E,0xD7,0x10,0x37,0x19,0xD2,0x18,0x3B,0x10,0xB9,0x73,0x19 },
    .encode = (gen_encode*)encode_poll_frame,
    .decode = (gen_decode*)decode_poll_frame,
    .min_size = 1,
    .max_size = 1,
  },
  {
    .name = "res_poll",
    .hash = { 0x6C,0x65,0x28,0x9F,0x80,0xBB,0x01,0x55,0xF5,0x1E,0x56,0xDC,0xA3,0x10,0xE6,0x0C,0x5F,0xA4,0xC0,0x84 },
    .encode = (gen_encode*)encode_res_poll,
    .decode = (gen_decode*)decode_res_poll,
    .min_size = 2,
    .max_size = 2,
  },
  {
    .name = "cmd_send",
    .hash = { 0x0F,0x25,0x99,0xB0,0xB2,0x55,0xEF,0x27,0x62,0x89,0xBC,0x43,0x14,0xAA,0x38,0x6C,0x1D,0x5A,0x7A,0xC0 },
    .encode = (gen_encode*)encode_cmd_send,
    .decode = (gen_decode*)decode_cmd_send,
    .min_size = 2,
    .max_size = 2,
  },
  {
    .name = "cmd_poll",
    .hash = { 0x85,0x44,0xF4,0x86,0x0E,0x31,0x0E,0x06,0xC1,0x0B,0xBB,0x87,0x37,0xB8,0xF8,0x3D,0x61,0x37,0x6B,0x84 },
    .encode = (gen_encode*)encode_cmd_poll,
    .decode = (gen_decode*)decode_cmd_poll,
    .min_size = 1,
    .max_size = 1,
  },
  {
    .name = "cmd_mac",
    .hash = { 0x28,0xCA,0xED,0x17,0x72,0xFB,0x1C,0x68,0xAA,0xDE,0x8B,0x3C,0x4B,0xA6,0xAB,0xDC,0x1B,0xFD,0x49,0x81 },
    .encode = (gen_encode*)encode_cmd_mac,
    .decode = (gen_decode*)decode_cmd_mac,
    .min_size = 1,
    .max_size = 1,
  },
  {
    .name = "cmd_info",
    .hash = { 0x14,0x1E,0xAF,0x55,0xC7,0xAF,0x6F,0x09,0x24,0x6F,0xD6,0x89,0xFC,0xA3,0xB1,0x8A,0xB0,0x9E,0x1A,0x50 },
    .encode = (gen_encode*)encode_cmd_info,
    .decode = (gen_decode*)decode_cmd_info,
    .min_size = 1,
    .max_size = 1,
  },
  {
    .name = "cmd_connected",
    .hash = { 0x1C,0x71,0x94,0xAF,0x95,0xE6,0x73,0x28,0x1A,0xDE,0x84,0x2C,0xA0,0x4C,0x55,0xA9,0x77,0x16,0xF2,0x9C },
    .encode = (gen_encode*)encode_cmd_connected,
    .decode = (gen_decode*)decode_cmd_connected,
    .min_size = 1,
    .max_size = 1,
  },
  {
    .name = "atom_baud",
    .hash = { 0x67,0x5C,0x79,0x9F,0x14,0xE8,0xE2,0x11,0xD1,0x4C,0xCD,0x67,0xBF,0x8B,0x54,0xBE,0x19,0x9D,0xC1,0x7A },
    .encode = (gen_encode*)encode_atom_baud,
    .decode = (gen_decode*)decode_atom_baud,
    .min_size = 1,
    .max_size = 1,
  },
  {
    .name = "cmd_baud",
    .hash = { 0x6D,0x61,0x87,0xDC,0x5B,0x15,0xA9,0xA1,0x8A,0x0B,0x4E,0xD6,0x00,0x49,0xCA,0x19,0x85,0xF6,0xAB,0xAB },
    .encode = (gen_encode*)encode_cmd_baud,
    .decode = (gen_decode*)decode_cmd_baud,
    .min_size = 2,
    .max_size = 2,
  },
  {
    .name = "arr_u8_32",
    .hash = { 0x50,0x51,0x07,0x7D,0xE0,0xF3,0x75,0x5B,0x22,0xB9,0xAA,0xFA,0x6B,0xA8,0xFB,0x38,0xFE,0xD6,0x01,0xFF },
    .encode = (gen_encode*)encode_arr_u8_32,
    .decode = (gen_decode*)decode_arr_u8_32,
    .min_size = 32,
    .max_size = 32,
  },
  {
    .name = "connection",
    .hash = { 0x75,0xCC,0x13,0xF8,0xE2,0xAB,0x40,0x6C,0xFA,0x68,0x6F,0x3D,0x88,0x08,0x30,0x0C,0xA7,0x96,0xCE,0xB9 },
    .encode = (gen_encode*)encode_connection,
    .decode = (gen_decode*)decode_connection,
    .min_size = 60,
    .max_size = 60,
  },
  {
    .name = "req_connect",
    .hash = { 0x86,0x74,0x72,0x2D,0x96,0x30,0x02,0xF4,0xD2,0xDF,0x45,0xFC,0xE9,0xD6,0xBC,0xB0,0xB4,0xB2,0xF7,0x3C },
    .encode = (gen_encode*)encode_req_connect,
    .decode = (gen_decode*)decode_req_connect,
    .min_size = 1,
    .max_size = 1,
  },
  {
    .name = "cmd_connect",
    .hash = { 0xD9,0x1F,0x43,0xFD,0x80,0x69,0x30,0x9B,0x95,0x95,0xB9,0x63,0x06,0xD0,0x2E,0x05,0x8C,0xAD,0x2D,0xFD },
    .encode = (gen_encode*)encode_cmd_connect,
    .decode = (gen_decode*)decode_cmd_connect,
    .min_size = 2,
    .max_size = 2,
  },
  {
    .name = "sleep_connection",
    .hash = { 0x15,0xAD,0xC0,0x9C,0xAE,0x94,0x94,0x3B,0xB0,0x62,0x93,0x87,0x36,0x27,0xB3,0x6C,0xBD,0x15,0x59,0x87 },
    .encode = (gen_encode*)encode_sleep_connection,
    .decode = (gen_decode*)decode_sleep_connection,
    .min_size = 1,
    .max_size = 1,
  },
  {
    .name = "res_sleep",
    .hash = { 0xBB,0xA1,0x6A,0x74,0x0D,0xBD,0xE8,0xD6,0x22,0xE8,0x49,0xF2,0xFA,0xF9,0x4D,0x97,0x5C,0xAC,0x6E,0x1D },
    .encode = (gen_encode*)encode_res_sleep,
    .decode = (gen_decode*)decode_res_sleep,
    .min_size = 2,
    .max_size = 2,
  },
  {
    .name = "cmd_sleep",
    .hash = { 0x22,0x3C,0x88,0x89,0x8B,0xF6,0x45,0x95,0x56,0x2C,0xA4,0x5C,0x51,0x10,0xA0,0x7E,0x8E,0x38,0xF7,0xF9 },
    .encode = (gen_encode*)encode_cmd_sleep,
    .decode = (gen_decode*)decode_cmd_sleep,
    .min_size = 1,
    .max_size = 1,
  },
  {
    .name = "cmd",
    .hash = { 0xEA,0xE2,0x53,0xB3,0xAA,0x06,0x1B,0x41,0x0E,0x5D,0x15,0x97,0x56,0x00,0xF0,0x6D,0x76,0xCC,0xC7,0x6C },
    .encode = (gen_encode*)encode_cmd,
    .decode = (gen_decode*)decode_cmd,
    .min_size = 2,
    .max_size = 2,
  },
  {
    .name = "txn",
    .hash = { 0xBF,0x55,0x00,0x9E,0x1F,0x54,0xB0,0x4F,0xDE,0x49,0x2C,0x54,0x77,0x95,0x20,0x94,0xF8,0xEE,0x3A,0x22 },
    .encode = (gen_encode*)encode_txn,
    .decode = (gen_decode*)decode_txn,
    .min_size = 4,
    .max_size = 4,
  }
};

/* message interface */
R encode_message_atom_api(EI * const _iter, struct message_atom_api const * const _obj) {
  const struct caut_type_descriptor * const desc = &type_descriptors[_obj->_type];
  size_t _data_position = 0;
  uint8_t _data_len = 0;
  void * len_ptr = 0;

  STATUS_CHECK(__caut_encode_reserve(_iter, LENGTH_WIDTH_atom_api, &len_ptr));
  STATUS_CHECK(__caut_encode_raw_bytes(_iter, desc->hash, TYPE_TAG_WIDTH_atom_api));
  _data_position = _iter->position;
  STATUS_CHECK(desc->encode(_iter, &_obj->_data));
  _data_len = (uint8_t)(_iter->position - _data_position);

  memmove(len_ptr, &_data_len, sizeof(_data_len));

  return caut_status_ok;
}

R decode_message_header_atom_api(DI * const _iter, struct message_header_atom_api * const _header) {
  uint8_t length = 0;
  STATUS_CHECK(decode_u8(_iter, &length));
  _header->length = length;
  STATUS_CHECK(__caut_decode_raw_bytes(_iter, _header->tag, sizeof(_header->tag)));

  return caut_status_ok;
}

R decode_message_atom_api(DI * const _iter, struct message_header_atom_api const * const _header, struct message_atom_api * const _obj) {
  const struct caut_type_descriptor * desc = 0;

  for (size_t i = 0; i < ARR_LEN(type_descriptors); i++) {
    if (0 == memcmp(_header->tag, type_descriptors[i].hash, TYPE_TAG_WIDTH_atom_api)) {
      desc = &type_descriptors[i];
      _obj->_type = (enum type_index_atom_api)i;
      break;
    }
  }

  if (0 == desc) {
    return caut_status_invalid_tag;
  } else {
    STATUS_CHECK(desc->decode(_iter, &_obj->_data));
  }

  return caut_status_ok;
}
