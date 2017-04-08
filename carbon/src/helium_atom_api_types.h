#ifndef _CAUTERIZE_C11STREAM_helium_atom_api_TYPES_
#define _CAUTERIZE_C11STREAM_helium_atom_api_TYPES_

#include "cauterize.h"
#include <stdint.h>

#include "helium_atom_api_infodefines.h"

#define NAME_helium_atom_api "helium_atom_api"
#define VERSION_helium_atom_api "0.0.0.1"
#define NUM_TYPES_helium_atom_api (124)
#define MIN_SIZE_helium_atom_api SCHEMA_SIZE_MIN_helium_atom_api
#define MAX_SIZE_helium_atom_api SCHEMA_SIZE_MAX_helium_atom_api


/* type definitions */
#define   VECTOR_MAX_LEN_s_ssk (32)
struct s_ssk {
  caut_tag8_t _length;
  uint8_t elems[  VECTOR_MAX_LEN_s_ssk];
};

#define   VECTOR_MAX_LEN_s_sig (8)
struct s_sig {
  caut_tag8_t _length;
  uint8_t elems[  VECTOR_MAX_LEN_s_sig];
};

#define   VECTOR_MAX_LEN_s_sigs (8)
struct s_sigs {
  caut_tag8_t _length;
  struct s_sig elems[  VECTOR_MAX_LEN_s_sigs];
};

#define ENUM_MAX_VAL_s_sec_type (s_sec_type_s_ecc)
enum s_sec_type {
  s_sec_type_s_sha_204 = 0,
  s_sec_type_s_ecc = 1,
};

#define   VECTOR_MAX_LEN_s_part_num (13)
struct s_part_num {
  caut_tag8_t _length;
  uint8_t elems[  VECTOR_MAX_LEN_s_part_num];
};

#define ENUM_MAX_VAL_s_lstat (s_lstat_s_lstat_cfg_data_locked)
enum s_lstat {
  s_lstat_s_lstat_unlocked = 0,
  s_lstat_s_lstat_cfg_locked = 1,
  s_lstat_s_lstat_data_locked = 2,
  s_lstat_s_lstat_cfg_data_locked = 3,
};

#define   VECTOR_MAX_LEN_s_key_sigs (69)
struct s_key_sigs {
  caut_tag8_t _length;
  uint8_t elems[  VECTOR_MAX_LEN_s_key_sigs];
};

#define   VECTOR_MAX_LEN_s_key_sig_req (37)
struct s_key_sig_req {
  caut_tag8_t _length;
  uint8_t elems[  VECTOR_MAX_LEN_s_key_sig_req];
};

struct s_key_sig_req_rec {
  uint8_t key_slot;
  struct s_key_sig_req key_req;
};

struct s_gen_session_key_req {
  uint32_t nonce;
  uint8_t slot;
};

#define ENUM_MAX_VAL_power_cmd (power_cmd_power_off)
enum power_cmd {
  power_cmd_power_on = 0,
  power_cmd_power_off = 1,
};

#define   VECTOR_MAX_LEN_pan_frame (107)
struct pan_frame {
  caut_tag8_t _length;
  uint8_t elems[  VECTOR_MAX_LEN_pan_frame];
};

#define ENUM_MAX_VAL_pan_cmd (pan_cmd_start_pan)
enum pan_cmd {
  pan_cmd_stop_pan = 0,
  pan_cmd_start_pan = 1,
};

#define ENUM_MAX_VAL_n_send_tx_status (n_send_tx_status_nack)
enum n_send_tx_status {
  n_send_tx_status_ack = 0,
  n_send_tx_status_channel_access_failure = 1,
  n_send_tx_status_nack = 2,
};

struct n_send_req {
  struct pan_frame payload;
};

struct n_send_metadata {
  enum n_send_tx_status tx_status;
};

#define ENUM_MAX_VAL_n_send_err (n_send_err_not_autonomous)
enum n_send_err {
  n_send_err_not_connected = 0,
  n_send_err_radio_cant_send = 1,
  n_send_err_dropped = 2,
  n_send_err_payload_len = 3,
  n_send_err_not_autonomous = 4,
};

#define UNION_NUM_FIELDS_n_send_resp (0x2ull)
struct n_send_resp {
  enum n_send_resp_tag {
    n_send_resp_tag_err = 0,
    n_send_resp_tag_ok = 1,
  } _tag;


  union {
    enum n_send_err err;
    struct n_send_metadata ok;
  };

};

#define ENUM_MAX_VAL_n_mode (n_mode_autonomous)
enum n_mode {
  n_mode_api = 0,
  n_mode_autonomous = 1,
};

#define   ARRAY_LEN_n_img_sha (32)
struct n_img_sha {
  uint8_t elems[  ARRAY_LEN_n_img_sha];
};

struct n_reflash_header {
  uint32_t size;
  struct n_img_sha sha;
};

#define   ARRAY_LEN_n_img_id (4)
struct n_img_id {
  uint8_t elems[  ARRAY_LEN_n_img_id];
};

#define   VECTOR_MAX_LEN_n_img_data (256)
struct n_img_data {
  caut_tag16_t _length;
  uint8_t elems[  VECTOR_MAX_LEN_n_img_data];
};

struct n_reflash_data {
  struct n_img_id transfer_id;
  uint32_t offset;
  struct n_img_data data;
};

#define UNION_NUM_FIELDS_n_cmd_send (0x2ull)
struct n_cmd_send {
  enum n_cmd_send_tag {
    n_cmd_send_tag_req = 0,
    n_cmd_send_tag_resp = 1,
  } _tag;


  union {
    struct n_send_req req;
    struct n_send_resp resp;
  };

};

#define ENUM_MAX_VAL_n_cmd_reflash_header_resp (n_cmd_reflash_header_resp_err_size)
enum n_cmd_reflash_header_resp {
  n_cmd_reflash_header_resp_ok = 0,
  n_cmd_reflash_header_resp_ok_duplicate = 1,
  n_cmd_reflash_header_resp_err_size = 2,
};

#define UNION_NUM_FIELDS_n_cmd_reflash_header (0x2ull)
struct n_cmd_reflash_header {
  enum n_cmd_reflash_header_tag {
    n_cmd_reflash_header_tag_req = 0,
    n_cmd_reflash_header_tag_resp = 1,
  } _tag;


  union {
    struct n_reflash_header req;
    enum n_cmd_reflash_header_resp resp;
  };

};

#define UNION_NUM_FIELDS_n_cmd_reflash_data_resp (0x6ull)
struct n_cmd_reflash_data_resp {
  enum n_cmd_reflash_data_resp_tag {
    n_cmd_reflash_data_resp_tag_ok_finished = 0,
    n_cmd_reflash_data_resp_tag_ok_not_finished = 1,
    n_cmd_reflash_data_resp_tag_err_no_transfer = 2,
    n_cmd_reflash_data_resp_tag_err_out_of_order = 3,
    n_cmd_reflash_data_resp_tag_err_transfer_id_mismatch = 4,
    n_cmd_reflash_data_resp_tag_err_sha_mismatch = 5,
  } _tag;


  union {
    /* no data for field ok_finished with index 0 */
    /* no data for field ok_not_finished with index 1 */
    /* no data for field err_no_transfer with index 2 */
    uint32_t err_out_of_order;
    struct n_img_id err_transfer_id_mismatch;
    struct n_img_sha err_sha_mismatch;
  };

};

#define UNION_NUM_FIELDS_n_cmd_reflash_data (0x2ull)
struct n_cmd_reflash_data {
  enum n_cmd_reflash_data_tag {
    n_cmd_reflash_data_tag_req = 0,
    n_cmd_reflash_data_tag_resp = 1,
  } _tag;


  union {
    struct n_reflash_data req;
    struct n_cmd_reflash_data_resp resp;
  };

};

#define UNION_NUM_FIELDS_n_cmd_get_mode (0x2ull)
struct n_cmd_get_mode {
  enum n_cmd_get_mode_tag {
    n_cmd_get_mode_tag_req = 0,
    n_cmd_get_mode_tag_resp = 1,
  } _tag;


  union {
    /* no data for field req with index 0 */
    enum n_mode resp;
  };

};

struct n_cmd_connection_status_resp {
  bool connected;
};

#define UNION_NUM_FIELDS_n_cmd_connection_status (0x2ull)
struct n_cmd_connection_status {
  enum n_cmd_connection_status_tag {
    n_cmd_connection_status_tag_req = 0,
    n_cmd_connection_status_tag_resp = 1,
  } _tag;


  union {
    /* no data for field req with index 0 */
    struct n_cmd_connection_status_resp resp;
  };

};

#define ENUM_MAX_VAL_n_cmd_connect_resp (n_cmd_connect_resp_err_fallback_to_slow_connect)
enum n_cmd_connect_resp {
  n_cmd_connect_resp_ok = 0,
  n_cmd_connect_resp_err_not_autonomous = 1,
  n_cmd_connect_resp_err_fallback_to_slow_connect = 2,
};

#define   VECTOR_MAX_LEN_h_scan (64)
struct h_scan {
  caut_tag8_t _length;
  uint8_t elems[  VECTOR_MAX_LEN_h_scan];
};

#define   VECTOR_MAX_LEN_h_mfg_data (32)
struct h_mfg_data {
  caut_tag8_t _length;
  uint8_t elems[  VECTOR_MAX_LEN_h_mfg_data];
};


typedef uint64_t h_mac; /* synonym */

struct s_get_derived_key_req {
  uint8_t key_slot;
  h_mac long_add;
};


typedef uint8_t h_data_u8; /* synonym */


typedef uint32_t h_data_u32; /* synonym */


typedef uint16_t h_data_u16; /* synonym */

#define   VECTOR_MAX_LEN_h_buf_32b (32)
struct h_buf_32b {
  caut_tag8_t _length;
  uint8_t elems[  VECTOR_MAX_LEN_h_buf_32b];
};

struct s_key_update_req {
  uint8_t key_slot;
  struct h_buf_32b random;
  struct h_buf_32b mac;
};

#define   VECTOR_MAX_LEN_h_buf_20b (20)
struct h_buf_20b {
  caut_tag8_t _length;
  uint8_t elems[  VECTOR_MAX_LEN_h_buf_20b];
};

#define   VECTOR_MAX_LEN_h_buf (128)
struct h_buf {
  caut_tag8_t _length;
  uint8_t elems[  VECTOR_MAX_LEN_h_buf];
};

#define   ARRAY_LEN_h_arr_32b (32)
struct h_arr_32b {
  uint8_t elems[  ARRAY_LEN_h_arr_32b];
};

#define ENUM_MAX_VAL_beacon_cmd (beacon_cmd_start_beacon)
enum beacon_cmd {
  beacon_cmd_stop_beacon = 0,
  beacon_cmd_start_beacon = 1,
};

struct a_version {
  uint8_t product;
  uint8_t major;
  uint8_t minor;
  uint8_t patch;
};

struct n_connection {
  uint64_t long_addr;
  uint16_t pan_id;
  uint16_t short_addr;
  uint16_t gateway_addr;
  uint8_t pan_seq;
  uint8_t radio_index;
  uint8_t connected;
  uint8_t channel;
  uint8_t speed;
  uint8_t key_slot;
  struct h_arr_32b sess_key;
  struct a_version fw_version;
};

#define UNION_NUM_FIELDS_n_cmd_sleep_resp (0x5ull)
struct n_cmd_sleep_resp {
  enum n_cmd_sleep_resp_tag {
    n_cmd_sleep_resp_tag_not_connected = 0,
    n_cmd_sleep_resp_tag_not_autonomous = 1,
    n_cmd_sleep_resp_tag_keep_awake = 2,
    n_cmd_sleep_resp_tag_connection = 3,
    n_cmd_sleep_resp_tag_needs_reset = 4,
  } _tag;


  union {
    /* no data for field not_connected with index 0 */
    /* no data for field not_autonomous with index 1 */
    /* no data for field keep_awake with index 2 */
    struct n_connection connection;
    /* no data for field needs_reset with index 4 */
  };

};

#define UNION_NUM_FIELDS_n_cmd_sleep (0x2ull)
struct n_cmd_sleep {
  enum n_cmd_sleep_tag {
    n_cmd_sleep_tag_req = 0,
    n_cmd_sleep_tag_resp = 1,
  } _tag;


  union {
    /* no data for field req with index 0 */
    struct n_cmd_sleep_resp resp;
  };

};

struct n_connection_quick {
  uint32_t time;
  struct n_connection connection;
};

#define UNION_NUM_FIELDS_n_cmd_connect_req (0x2ull)
struct n_cmd_connect_req {
  enum n_cmd_connect_req_tag {
    n_cmd_connect_req_tag_cold = 0,
    n_cmd_connect_req_tag_quick = 1,
  } _tag;


  union {
    /* no data for field cold with index 0 */
    struct n_connection_quick quick;
  };

};

#define UNION_NUM_FIELDS_n_cmd_connect (0x2ull)
struct n_cmd_connect {
  enum n_cmd_connect_tag {
    n_cmd_connect_tag_req = 0,
    n_cmd_connect_tag_resp = 1,
  } _tag;


  union {
    struct n_cmd_connect_req req;
    enum n_cmd_connect_resp resp;
  };

};

struct a_time {
  uint32_t sec;
  uint16_t msec;
};

#define ENUM_MAX_VAL_a_status (a_status_error)
enum a_status {
  a_status_success = 0,
  a_status_error = 1,
};

struct r_cmd_get_info_resp {
  enum a_status status;
  uint8_t part_num;
  uint8_t min_channel;
  uint8_t max_channel;
  uint16_t pan_id;
  uint16_t short_addr;
  uint8_t channel;
  uint8_t beaconing;
};

struct s_gen_session_key_resp {
  enum a_status status;
  struct h_buf_32b session_key;
};

#define UNION_NUM_FIELDS_s_cmd_gen_session_key (0x2ull)
struct s_cmd_gen_session_key {
  enum s_cmd_gen_session_key_tag {
    s_cmd_gen_session_key_tag_req = 0,
    s_cmd_gen_session_key_tag_resp = 1,
  } _tag;


  union {
    struct s_gen_session_key_req req;
    struct s_gen_session_key_resp resp;
  };

};

struct s_get_derived_key_resp {
  struct s_ssk ssk;
  enum a_status status;
};

#define UNION_NUM_FIELDS_s_cmd_get_derived_key (0x2ull)
struct s_cmd_get_derived_key {
  enum s_cmd_get_derived_key_tag {
    s_cmd_get_derived_key_tag_req = 0,
    s_cmd_get_derived_key_tag_resp = 1,
  } _tag;


  union {
    struct s_get_derived_key_req req;
    struct s_get_derived_key_resp resp;
  };

};

struct s_key_sig_resp {
  enum a_status status;
  struct s_key_sigs sigs;
};

#define UNION_NUM_FIELDS_s_cmd_key_sigs (0x2ull)
struct s_cmd_key_sigs {
  enum s_cmd_key_sigs_tag {
    s_cmd_key_sigs_tag_req = 0,
    s_cmd_key_sigs_tag_resp = 1,
  } _tag;


  union {
    struct s_key_sig_req_rec req;
    struct s_key_sig_resp resp;
  };

};

struct s_resp_key_create {
  enum a_status status;
  struct h_buf_32b key;
  uint16_t key_crc;
};

#define UNION_NUM_FIELDS_s_cmd_key_create (0x2ull)
struct s_cmd_key_create {
  enum s_cmd_key_create_tag {
    s_cmd_key_create_tag_req_key_slot = 0,
    s_cmd_key_create_tag_resp = 1,
  } _tag;


  union {
    uint8_t req_key_slot;
    struct s_resp_key_create resp;
  };

};

struct s_resp_lstat {
  enum a_status status;
  enum s_lstat lstat;
};

#define UNION_NUM_FIELDS_s_cmd_read_lstat (0x2ull)
struct s_cmd_read_lstat {
  enum s_cmd_read_lstat_tag {
    s_cmd_read_lstat_tag_req = 0,
    s_cmd_read_lstat_tag_resp = 1,
  } _tag;


  union {
    /* no data for field req with index 0 */
    struct s_resp_lstat resp;
  };

};

struct s_resp_part {
  enum a_status status;
  struct s_part_num sec_part_num;
};

#define UNION_NUM_FIELDS_s_cmd_read_part (0x2ull)
struct s_cmd_read_part {
  enum s_cmd_read_part_tag {
    s_cmd_read_part_tag_req = 0,
    s_cmd_read_part_tag_resp = 1,
  } _tag;


  union {
    /* no data for field req with index 0 */
    struct s_resp_part resp;
  };

};

#define ENUM_MAX_VAL_a_sleep_mode (a_sleep_mode_sleep_with_config)
enum a_sleep_mode {
  a_sleep_mode_no_sleep = 0,
  a_sleep_mode_sleep_with_config = 1,
};

struct a_resp_u8 {
  enum a_status status;
  uint8_t value;
};

struct a_resp_u64 {
  enum a_status status;
  uint64_t value;
};

struct a_resp_sleep_mode {
  enum a_status status;
  enum a_sleep_mode sleep_mode;
};

struct a_resp_mfg_data {
  enum a_status status;
  struct h_mfg_data value;
};

struct a_resp_get_atom_info {
  enum a_status status;
  uint8_t radio_count;
  uint32_t uptime;
  struct a_time time;
  struct a_version fw_version;
  struct h_buf_20b schema_fp;
};

struct a_resp_gen {
  enum a_status status;
};

#define UNION_NUM_FIELDS_n_cmd_set_mode (0x2ull)
struct n_cmd_set_mode {
  enum n_cmd_set_mode_tag {
    n_cmd_set_mode_tag_req = 0,
    n_cmd_set_mode_tag_resp = 1,
  } _tag;


  union {
    enum n_mode req;
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_r_cmd_beacon (0x2ull)
struct r_cmd_beacon {
  enum r_cmd_beacon_tag {
    r_cmd_beacon_tag_req = 0,
    r_cmd_beacon_tag_resp = 1,
  } _tag;


  union {
    enum beacon_cmd req;
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_r_cmd_pan (0x2ull)
struct r_cmd_pan {
  enum r_cmd_pan_tag {
    r_cmd_pan_tag_req = 0,
    r_cmd_pan_tag_resp = 1,
  } _tag;


  union {
    enum pan_cmd req;
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_r_cmd_pan_fr (0x2ull)
struct r_cmd_pan_fr {
  enum r_cmd_pan_fr_tag {
    r_cmd_pan_fr_tag_req = 0,
    r_cmd_pan_fr_tag_resp = 1,
  } _tag;


  union {
    struct pan_frame req;
    struct a_resp_gen resp;
  };

};

struct r_cmd_power {
  enum power_cmd req;
  struct a_resp_gen resp;
};

#define UNION_NUM_FIELDS_r_cmd_scan_start (0x2ull)
struct r_cmd_scan_start {
  enum r_cmd_scan_start_tag {
    r_cmd_scan_start_tag_req = 0,
    r_cmd_scan_start_tag_resp = 1,
  } _tag;


  union {
    /* no data for field req with index 0 */
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_r_cmd_set_chan (0x2ull)
struct r_cmd_set_chan {
  enum r_cmd_set_chan_tag {
    r_cmd_set_chan_tag_req = 0,
    r_cmd_set_chan_tag_resp = 1,
  } _tag;


  union {
    uint8_t req;
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_r_cmd_set_pan_id (0x2ull)
struct r_cmd_set_pan_id {
  enum r_cmd_set_pan_id_tag {
    r_cmd_set_pan_id_tag_req = 0,
    r_cmd_set_pan_id_tag_resp = 1,
  } _tag;


  union {
    uint16_t req;
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_r_cmd_set_sh_addr (0x2ull)
struct r_cmd_set_sh_addr {
  enum r_cmd_set_sh_addr_tag {
    r_cmd_set_sh_addr_tag_req = 0,
    r_cmd_set_sh_addr_tag_resp = 1,
  } _tag;


  union {
    uint16_t req;
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_s_cmd_init (0x2ull)
struct s_cmd_init {
  enum s_cmd_init_tag {
    s_cmd_init_tag_req = 0,
    s_cmd_init_tag_resp = 1,
  } _tag;


  union {
    /* no data for field req with index 0 */
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_s_cmd_key_update (0x2ull)
struct s_cmd_key_update {
  enum s_cmd_key_update_tag {
    s_cmd_key_update_tag_req = 0,
    s_cmd_key_update_tag_resp = 1,
  } _tag;


  union {
    struct s_key_update_req req;
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_s_cmd_lock (0x2ull)
struct s_cmd_lock {
  enum s_cmd_lock_tag {
    s_cmd_lock_tag_req = 0,
    s_cmd_lock_tag_resp = 1,
  } _tag;


  union {
    /* no data for field req with index 0 */
    struct a_resp_gen resp;
  };

};

#define ENUM_MAX_VAL_a_radio_type (a_radio_type_r_24_g)
enum a_radio_type {
  a_radio_type_r_sub_g = 0,
  a_radio_type_r_24_g = 1,
};

#define UNION_NUM_FIELDS_r_cmd_get_info (0x2ull)
struct r_cmd_get_info {
  enum r_cmd_get_info_tag {
    r_cmd_get_info_tag_req_rtype = 0,
    r_cmd_get_info_tag_resp = 1,
  } _tag;


  union {
    enum a_radio_type req_rtype;
    struct r_cmd_get_info_resp resp;
  };

};

#define UNION_NUM_FIELDS_r_cmd (0x9ull)
struct r_cmd {
  enum r_cmd_tag {
    r_cmd_tag_scan_start = 0,
    r_cmd_tag_set_pan_id = 1,
    r_cmd_tag_set_sh_addr = 2,
    r_cmd_tag_set_channel = 3,
    r_cmd_tag_pan = 4,
    r_cmd_tag_beacon = 5,
    r_cmd_tag_pan_fr = 6,
    r_cmd_tag_power = 7,
    r_cmd_tag_get_info = 8,
  } _tag;


  union {
    struct r_cmd_scan_start scan_start;
    struct r_cmd_set_pan_id set_pan_id;
    struct r_cmd_set_sh_addr set_sh_addr;
    struct r_cmd_set_chan set_channel;
    struct r_cmd_pan pan;
    struct r_cmd_beacon beacon;
    struct r_cmd_pan_fr pan_fr;
    struct r_cmd_power power;
    struct r_cmd_get_info get_info;
  };

};

#define ENUM_MAX_VAL_a_op_mode (a_op_mode_maintenence)
enum a_op_mode {
  a_op_mode_default = 0,
  a_op_mode_maintenence = 1,
};

#define   VECTOR_MAX_LEN_a_debug_msg (80)
struct a_debug_msg {
  caut_tag8_t _length;
  uint8_t elems[  VECTOR_MAX_LEN_a_debug_msg];
};

struct a_data {
  struct h_buf buf;
};

#define UNION_NUM_FIELDS_n_poll_data (0x4ull)
struct n_poll_data {
  enum n_poll_data_tag {
    n_poll_data_tag_none = 0,
    n_poll_data_tag_frame = 1,
    n_poll_data_tag_err_not_autonomous = 2,
    n_poll_data_tag_need_reset = 3,
  } _tag;


  union {
    /* no data for field none with index 0 */
    struct a_data frame;
    /* no data for field err_not_autonomous with index 2 */
    /* no data for field need_reset with index 3 */
  };

};

struct n_cmd_poll_data_resp {
  uint32_t frames_droped;
  struct n_poll_data poll_data;
};

#define UNION_NUM_FIELDS_n_cmd_poll_data (0x2ull)
struct n_cmd_poll_data {
  enum n_cmd_poll_data_tag {
    n_cmd_poll_data_tag_req = 0,
    n_cmd_poll_data_tag_resp = 1,
  } _tag;


  union {
    /* no data for field req with index 0 */
    struct n_cmd_poll_data_resp resp;
  };

};

#define UNION_NUM_FIELDS_a_cmd_security (0x8ull)
struct a_cmd_security {
  enum a_cmd_security_tag {
    a_cmd_security_tag_read_part = 0,
    a_cmd_security_tag_init = 1,
    a_cmd_security_tag_read_lstat = 2,
    a_cmd_security_tag_key_create = 3,
    a_cmd_security_tag_key_update = 4,
    a_cmd_security_tag_lock = 5,
    a_cmd_security_tag_get_key_sigs = 6,
    a_cmd_security_tag_gen_session_key = 7,
  } _tag;


  union {
    struct s_cmd_read_part read_part;
    struct s_cmd_init init;
    struct s_cmd_read_lstat read_lstat;
    struct s_cmd_key_create key_create;
    struct s_cmd_key_update key_update;
    struct s_cmd_lock lock;
    struct s_cmd_key_sigs get_key_sigs;
    struct s_cmd_gen_session_key gen_session_key;
  };

};

struct a_cmd_radio {
  enum a_radio_type radio_id;
  struct r_cmd cmd;
};

struct a_cmd_pin {
  uint8_t pin_num;
};

#define UNION_NUM_FIELDS_a_cmd_node (0x9ull)
struct a_cmd_node {
  enum a_cmd_node_tag {
    a_cmd_node_tag_set_mode = 0,
    a_cmd_node_tag_get_mode = 1,
    a_cmd_node_tag_reflash_header = 2,
    a_cmd_node_tag_reflash_data = 3,
    a_cmd_node_tag_send = 4,
    a_cmd_node_tag_connection_status = 5,
    a_cmd_node_tag_poll_data = 6,
    a_cmd_node_tag_connect = 7,
    a_cmd_node_tag_sleep = 8,
  } _tag;


  union {
    struct n_cmd_set_mode set_mode;
    struct n_cmd_get_mode get_mode;
    struct n_cmd_reflash_header reflash_header;
    struct n_cmd_reflash_data reflash_data;
    struct n_cmd_send send;
    struct n_cmd_connection_status connection_status;
    struct n_cmd_poll_data poll_data;
    struct n_cmd_connect connect;
    struct n_cmd_sleep sleep;
  };

};

#define UNION_NUM_FIELDS_a_cmd_config_set_time (0x2ull)
struct a_cmd_config_set_time {
  enum a_cmd_config_set_time_tag {
    a_cmd_config_set_time_tag_req = 0,
    a_cmd_config_set_time_tag_resp = 1,
  } _tag;


  union {
    struct a_time req;
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_a_cmd_config_set_sleep_mode (0x2ull)
struct a_cmd_config_set_sleep_mode {
  enum a_cmd_config_set_sleep_mode_tag {
    a_cmd_config_set_sleep_mode_tag_req = 0,
    a_cmd_config_set_sleep_mode_tag_resp = 1,
  } _tag;


  union {
    enum a_sleep_mode req;
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_a_cmd_config_set_op_mode (0x2ull)
struct a_cmd_config_set_op_mode {
  enum a_cmd_config_set_op_mode_tag {
    a_cmd_config_set_op_mode_tag_req = 0,
    a_cmd_config_set_op_mode_tag_resp = 1,
  } _tag;


  union {
    enum a_op_mode req;
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_a_cmd_config_set_mfg_data (0x2ull)
struct a_cmd_config_set_mfg_data {
  enum a_cmd_config_set_mfg_data_tag {
    a_cmd_config_set_mfg_data_tag_req = 0,
    a_cmd_config_set_mfg_data_tag_resp = 1,
  } _tag;


  union {
    struct h_mfg_data req;
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_a_cmd_config_set_mac (0x2ull)
struct a_cmd_config_set_mac {
  enum a_cmd_config_set_mac_tag {
    a_cmd_config_set_mac_tag_req = 0,
    a_cmd_config_set_mac_tag_resp = 1,
  } _tag;


  union {
    h_mac req;
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_a_cmd_config_read_sleep_mode (0x2ull)
struct a_cmd_config_read_sleep_mode {
  enum a_cmd_config_read_sleep_mode_tag {
    a_cmd_config_read_sleep_mode_tag_req = 0,
    a_cmd_config_read_sleep_mode_tag_resp = 1,
  } _tag;


  union {
    /* no data for field req with index 0 */
    struct a_resp_sleep_mode resp;
  };

};

#define UNION_NUM_FIELDS_a_cmd_config_read_mfg_data (0x2ull)
struct a_cmd_config_read_mfg_data {
  enum a_cmd_config_read_mfg_data_tag {
    a_cmd_config_read_mfg_data_tag_req = 0,
    a_cmd_config_read_mfg_data_tag_resp = 1,
  } _tag;


  union {
    /* no data for field req with index 0 */
    struct a_resp_mfg_data resp;
  };

};

#define UNION_NUM_FIELDS_a_cmd_config_read_mac (0x2ull)
struct a_cmd_config_read_mac {
  enum a_cmd_config_read_mac_tag {
    a_cmd_config_read_mac_tag_req = 0,
    a_cmd_config_read_mac_tag_resp = 1,
  } _tag;


  union {
    /* no data for field req with index 0 */
    struct a_resp_u64 resp;
  };

};

#define UNION_NUM_FIELDS_a_cmd_config_get_atom_info (0x2ull)
struct a_cmd_config_get_atom_info {
  enum a_cmd_config_get_atom_info_tag {
    a_cmd_config_get_atom_info_tag_req = 0,
    a_cmd_config_get_atom_info_tag_resp = 1,
  } _tag;


  union {
    /* no data for field req with index 0 */
    struct a_resp_get_atom_info resp;
  };

};

#define UNION_NUM_FIELDS_a_cmd_brd_reset (0x2ull)
struct a_cmd_brd_reset {
  enum a_cmd_brd_reset_tag {
    a_cmd_brd_reset_tag_req = 0,
    a_cmd_brd_reset_tag_resp = 1,
  } _tag;


  union {
    /* no data for field req with index 0 */
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_a_cmd_brd_pin_out (0x2ull)
struct a_cmd_brd_pin_out {
  enum a_cmd_brd_pin_out_tag {
    a_cmd_brd_pin_out_tag_req = 0,
    a_cmd_brd_pin_out_tag_resp = 1,
  } _tag;


  union {
    struct a_cmd_pin req;
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_a_cmd_brd_pin_in (0x2ull)
struct a_cmd_brd_pin_in {
  enum a_cmd_brd_pin_in_tag {
    a_cmd_brd_pin_in_tag_req = 0,
    a_cmd_brd_pin_in_tag_resp = 1,
  } _tag;


  union {
    struct a_cmd_pin req;
    struct a_resp_u8 resp;
  };

};

#define UNION_NUM_FIELDS_a_cmd_board (0x4ull)
struct a_cmd_board {
  enum a_cmd_board_tag {
    a_cmd_board_tag_reset = 0,
    a_cmd_board_tag_pin_set = 1,
    a_cmd_board_tag_pin_clear = 2,
    a_cmd_board_tag_pin_read = 3,
  } _tag;


  union {
    struct a_cmd_brd_reset reset;
    struct a_cmd_brd_pin_out pin_set;
    struct a_cmd_brd_pin_out pin_clear;
    struct a_cmd_brd_pin_in pin_read;
  };

};

struct a_channel_report {
  uint8_t channel;
  uint16_t energy;
};

#define   VECTOR_MAX_LEN_a_channel_reports (16)
struct a_channel_reports {
  caut_tag8_t _length;
  struct a_channel_report elems[  VECTOR_MAX_LEN_a_channel_reports];
};

struct a_beacon_report {
  uint16_t pan_id;
  uint16_t short_addr;
  uint8_t lqi;
  uint8_t ed;
  uint8_t channel;
  uint32_t time;
};

#define   VECTOR_MAX_LEN_a_beacon_reports (8)
struct a_beacon_reports {
  caut_tag8_t _length;
  struct a_beacon_report elems[  VECTOR_MAX_LEN_a_beacon_reports];
};

struct a_scan_report {
  uint8_t radio_index;
  struct a_channel_reports channels;
  struct a_beacon_reports beacons;
};

#define ENUM_MAX_VAL_a_baud_rate (a_baud_rate_br_256400)
enum a_baud_rate {
  a_baud_rate_br_9600 = 0,
  a_baud_rate_br_19200 = 1,
  a_baud_rate_br_38400 = 2,
  a_baud_rate_br_115200 = 3,
  a_baud_rate_br_256400 = 4,
};

#define UNION_NUM_FIELDS_a_cmd_config_read_baud_rate (0x2ull)
struct a_cmd_config_read_baud_rate {
  enum a_cmd_config_read_baud_rate_tag {
    a_cmd_config_read_baud_rate_tag_req = 0,
    a_cmd_config_read_baud_rate_tag_resp = 1,
  } _tag;


  union {
    /* no data for field req with index 0 */
    enum a_baud_rate resp;
  };

};

#define UNION_NUM_FIELDS_a_cmd_config_set_baud_rate (0x2ull)
struct a_cmd_config_set_baud_rate {
  enum a_cmd_config_set_baud_rate_tag {
    a_cmd_config_set_baud_rate_tag_req = 0,
    a_cmd_config_set_baud_rate_tag_resp = 1,
  } _tag;


  union {
    enum a_baud_rate req;
    struct a_resp_gen resp;
  };

};

#define UNION_NUM_FIELDS_a_cmd_config (0x11ull)
struct a_cmd_config {
  enum a_cmd_config_tag {
    a_cmd_config_tag_set_op_mode = 0,
    a_cmd_config_tag_set_mac = 1,
    a_cmd_config_tag_read_mac = 2,
    a_cmd_config_tag_set_mfg_data = 3,
    a_cmd_config_tag_read_mfg_data = 4,
    a_cmd_config_tag_set_sleep_mode = 5,
    a_cmd_config_tag_read_sleep_mode = 6,
    a_cmd_config_tag_set_baud_rate = 7,
    a_cmd_config_tag_read_baud_rate = 8,
    a_cmd_config_tag_set_time = 9,
    a_cmd_config_tag_get_atom_info = 10,
  } _tag;


  union {
    struct a_cmd_config_set_op_mode set_op_mode;
    struct a_cmd_config_set_mac set_mac;
    struct a_cmd_config_read_mac read_mac;
    struct a_cmd_config_set_mfg_data set_mfg_data;
    struct a_cmd_config_read_mfg_data read_mfg_data;
    struct a_cmd_config_set_sleep_mode set_sleep_mode;
    struct a_cmd_config_read_sleep_mode read_sleep_mode;
    struct a_cmd_config_set_baud_rate set_baud_rate;
    struct a_cmd_config_read_baud_rate read_baud_rate;
    struct a_cmd_config_set_time set_time;
    struct a_cmd_config_get_atom_info get_atom_info;
  };

};

#define UNION_NUM_FIELDS_a_cmd (0x8ull)
struct a_cmd {
  enum a_cmd_tag {
    a_cmd_tag_board_cmd = 0,
    a_cmd_tag_config_cmd = 1,
    a_cmd_tag_security_cmd = 2,
    a_cmd_tag_radio_cmd = 3,
    a_cmd_tag_data = 4,
    a_cmd_tag_scan_report = 5,
    a_cmd_tag_debug = 6,
    a_cmd_tag_node_cmd = 7,
  } _tag;


  union {
    struct a_cmd_board board_cmd;
    struct a_cmd_config config_cmd;
    struct a_cmd_security security_cmd;
    struct a_cmd_radio radio_cmd;
    struct a_data data;
    struct a_scan_report scan_report;
    struct a_debug_msg debug;
    struct a_cmd_node node_cmd;
  };

};

struct a_cmd_t {
  uint16_t sequence;
  struct a_cmd cmd;
};



#endif /* _CAUTERIZE_C11STREAM_helium_atom_api_TYPES_ */
