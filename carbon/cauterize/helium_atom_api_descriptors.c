#include "helium_atom_api_descriptors.h"
#include "helium_atom_api_types.h"

#include "cauterize_iterators.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define ARR_ELEM_SPAN(TYPE) \
  (uintptr_t)&(((TYPE *)NULL)[1])

struct caut_field const record_fields_helium_atom_api_s_key_sig_req_rec[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct s_key_sig_req_rec, key_slot) }, /* key_slot */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_s_key_sig_req, .offset = offsetof(struct s_key_sig_req_rec, key_req) }, /* key_req */
};

struct caut_field const record_fields_helium_atom_api_s_gen_session_key_req[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u32, .offset = offsetof(struct s_gen_session_key_req, nonce) }, /* nonce */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct s_gen_session_key_req, slot) }, /* slot */
};

struct caut_field const record_fields_helium_atom_api_n_send_req[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_pan_frame, .offset = offsetof(struct n_send_req, payload) }, /* payload */
};

struct caut_field const record_fields_helium_atom_api_n_send_metadata[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_n_send_tx_status, .offset = offsetof(struct n_send_metadata, tx_status) }, /* tx_status */
};

struct caut_field const union_fields_helium_atom_api_n_send_resp[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_n_send_err, .offset = offsetof(struct n_send_resp, err) }, /* err */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_n_send_metadata, .offset = offsetof(struct n_send_resp, ok) }, /* ok */
};

struct caut_field const record_fields_helium_atom_api_n_reflash_header[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u32, .offset = offsetof(struct n_reflash_header, size) }, /* size */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_n_img_sha, .offset = offsetof(struct n_reflash_header, sha) }, /* sha */
};

struct caut_field const record_fields_helium_atom_api_n_reflash_data[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_n_img_id, .offset = offsetof(struct n_reflash_data, transfer_id) }, /* transfer_id */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_u32, .offset = offsetof(struct n_reflash_data, offset) }, /* offset */
  { .field_index = 2, .data = true, .ref_id = type_id_helium_atom_api_n_img_data, .offset = offsetof(struct n_reflash_data, data) }, /* data */
};

struct caut_field const union_fields_helium_atom_api_n_cmd_send[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_n_send_req, .offset = offsetof(struct n_cmd_send, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_n_send_resp, .offset = offsetof(struct n_cmd_send, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_n_cmd_reflash_header[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_n_reflash_header, .offset = offsetof(struct n_cmd_reflash_header, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_reflash_header_resp, .offset = offsetof(struct n_cmd_reflash_header, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_n_cmd_reflash_data_resp[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* ok_finished */
  { .field_index = 1, .data = false, .ref_id = 0, .offset = 0 }, /* ok_not_finished */
  { .field_index = 2, .data = false, .ref_id = 0, .offset = 0 }, /* err_no_transfer */
  { .field_index = 3, .data = true, .ref_id = type_id_helium_atom_api_u32, .offset = offsetof(struct n_cmd_reflash_data_resp, err_out_of_order) }, /* err_out_of_order */
  { .field_index = 4, .data = true, .ref_id = type_id_helium_atom_api_n_img_id, .offset = offsetof(struct n_cmd_reflash_data_resp, err_transfer_id_mismatch) }, /* err_transfer_id_mismatch */
  { .field_index = 5, .data = true, .ref_id = type_id_helium_atom_api_n_img_sha, .offset = offsetof(struct n_cmd_reflash_data_resp, err_sha_mismatch) }, /* err_sha_mismatch */
};

struct caut_field const union_fields_helium_atom_api_n_cmd_reflash_data[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_n_reflash_data, .offset = offsetof(struct n_cmd_reflash_data, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_reflash_data_resp, .offset = offsetof(struct n_cmd_reflash_data, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_n_cmd_get_mode[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_n_mode, .offset = offsetof(struct n_cmd_get_mode, resp) }, /* resp */
};

struct caut_field const record_fields_helium_atom_api_n_cmd_connection_status_resp[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_bool, .offset = offsetof(struct n_cmd_connection_status_resp, connected) }, /* connected */
};

struct caut_field const union_fields_helium_atom_api_n_cmd_connection_status[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_connection_status_resp, .offset = offsetof(struct n_cmd_connection_status, resp) }, /* resp */
};

struct caut_field const record_fields_helium_atom_api_s_get_derived_key_req[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct s_get_derived_key_req, key_slot) }, /* key_slot */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_h_mac, .offset = offsetof(struct s_get_derived_key_req, long_add) }, /* long_add */
};

struct caut_field const record_fields_helium_atom_api_s_key_update_req[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct s_key_update_req, key_slot) }, /* key_slot */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_h_buf_32b, .offset = offsetof(struct s_key_update_req, random) }, /* random */
  { .field_index = 2, .data = true, .ref_id = type_id_helium_atom_api_h_buf_32b, .offset = offsetof(struct s_key_update_req, mac) }, /* mac */
};

struct caut_field const record_fields_helium_atom_api_a_version[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct a_version, product) }, /* product */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct a_version, major) }, /* major */
  { .field_index = 2, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct a_version, minor) }, /* minor */
  { .field_index = 3, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct a_version, patch) }, /* patch */
};

struct caut_field const record_fields_helium_atom_api_n_connection[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u64, .offset = offsetof(struct n_connection, long_addr) }, /* long_addr */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_u16, .offset = offsetof(struct n_connection, pan_id) }, /* pan_id */
  { .field_index = 2, .data = true, .ref_id = type_id_helium_atom_api_u16, .offset = offsetof(struct n_connection, short_addr) }, /* short_addr */
  { .field_index = 3, .data = true, .ref_id = type_id_helium_atom_api_u16, .offset = offsetof(struct n_connection, gateway_addr) }, /* gateway_addr */
  { .field_index = 4, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct n_connection, pan_seq) }, /* pan_seq */
  { .field_index = 5, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct n_connection, radio_index) }, /* radio_index */
  { .field_index = 6, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct n_connection, connected) }, /* connected */
  { .field_index = 7, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct n_connection, channel) }, /* channel */
  { .field_index = 8, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct n_connection, speed) }, /* speed */
  { .field_index = 9, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct n_connection, key_slot) }, /* key_slot */
  { .field_index = 10, .data = true, .ref_id = type_id_helium_atom_api_h_arr_32b, .offset = offsetof(struct n_connection, sess_key) }, /* sess_key */
  { .field_index = 11, .data = true, .ref_id = type_id_helium_atom_api_a_version, .offset = offsetof(struct n_connection, fw_version) }, /* fw_version */
};

struct caut_field const union_fields_helium_atom_api_n_cmd_sleep_resp[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* not_connected */
  { .field_index = 1, .data = false, .ref_id = 0, .offset = 0 }, /* not_autonomous */
  { .field_index = 2, .data = false, .ref_id = 0, .offset = 0 }, /* keep_awake */
  { .field_index = 3, .data = true, .ref_id = type_id_helium_atom_api_n_connection, .offset = offsetof(struct n_cmd_sleep_resp, connection) }, /* connection */
  { .field_index = 4, .data = false, .ref_id = 0, .offset = 0 }, /* needs_reset */
};

struct caut_field const union_fields_helium_atom_api_n_cmd_sleep[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_sleep_resp, .offset = offsetof(struct n_cmd_sleep, resp) }, /* resp */
};

struct caut_field const record_fields_helium_atom_api_n_connection_quick[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u32, .offset = offsetof(struct n_connection_quick, time) }, /* time */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_n_connection, .offset = offsetof(struct n_connection_quick, connection) }, /* connection */
};

struct caut_field const union_fields_helium_atom_api_n_cmd_connect_req[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* cold */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_n_connection_quick, .offset = offsetof(struct n_cmd_connect_req, quick) }, /* quick */
};

struct caut_field const union_fields_helium_atom_api_n_cmd_connect[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_connect_req, .offset = offsetof(struct n_cmd_connect, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_connect_resp, .offset = offsetof(struct n_cmd_connect, resp) }, /* resp */
};

struct caut_field const record_fields_helium_atom_api_a_time[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u32, .offset = offsetof(struct a_time, sec) }, /* sec */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_u16, .offset = offsetof(struct a_time, msec) }, /* msec */
};

struct caut_field const record_fields_helium_atom_api_r_cmd_get_info_resp[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_status, .offset = offsetof(struct r_cmd_get_info_resp, status) }, /* status */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct r_cmd_get_info_resp, part_num) }, /* part_num */
  { .field_index = 2, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct r_cmd_get_info_resp, min_channel) }, /* min_channel */
  { .field_index = 3, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct r_cmd_get_info_resp, max_channel) }, /* max_channel */
  { .field_index = 4, .data = true, .ref_id = type_id_helium_atom_api_u16, .offset = offsetof(struct r_cmd_get_info_resp, pan_id) }, /* pan_id */
  { .field_index = 5, .data = true, .ref_id = type_id_helium_atom_api_u16, .offset = offsetof(struct r_cmd_get_info_resp, short_addr) }, /* short_addr */
  { .field_index = 6, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct r_cmd_get_info_resp, channel) }, /* channel */
  { .field_index = 7, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct r_cmd_get_info_resp, beaconing) }, /* beaconing */
};

struct caut_field const record_fields_helium_atom_api_s_gen_session_key_resp[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_status, .offset = offsetof(struct s_gen_session_key_resp, status) }, /* status */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_h_buf_32b, .offset = offsetof(struct s_gen_session_key_resp, session_key) }, /* session_key */
};

struct caut_field const union_fields_helium_atom_api_s_cmd_gen_session_key[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_s_gen_session_key_req, .offset = offsetof(struct s_cmd_gen_session_key, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_s_gen_session_key_resp, .offset = offsetof(struct s_cmd_gen_session_key, resp) }, /* resp */
};

struct caut_field const record_fields_helium_atom_api_s_get_derived_key_resp[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_s_ssk, .offset = offsetof(struct s_get_derived_key_resp, ssk) }, /* ssk */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_status, .offset = offsetof(struct s_get_derived_key_resp, status) }, /* status */
};

struct caut_field const union_fields_helium_atom_api_s_cmd_get_derived_key[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_s_get_derived_key_req, .offset = offsetof(struct s_cmd_get_derived_key, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_s_get_derived_key_resp, .offset = offsetof(struct s_cmd_get_derived_key, resp) }, /* resp */
};

struct caut_field const record_fields_helium_atom_api_s_key_sig_resp[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_status, .offset = offsetof(struct s_key_sig_resp, status) }, /* status */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_s_key_sigs, .offset = offsetof(struct s_key_sig_resp, sigs) }, /* sigs */
};

struct caut_field const union_fields_helium_atom_api_s_cmd_key_sigs[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_s_key_sig_req_rec, .offset = offsetof(struct s_cmd_key_sigs, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_s_key_sig_resp, .offset = offsetof(struct s_cmd_key_sigs, resp) }, /* resp */
};

struct caut_field const record_fields_helium_atom_api_s_resp_key_create[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_status, .offset = offsetof(struct s_resp_key_create, status) }, /* status */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_h_buf_32b, .offset = offsetof(struct s_resp_key_create, key) }, /* key */
  { .field_index = 2, .data = true, .ref_id = type_id_helium_atom_api_u16, .offset = offsetof(struct s_resp_key_create, key_crc) }, /* key_crc */
};

struct caut_field const union_fields_helium_atom_api_s_cmd_key_create[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct s_cmd_key_create, req_key_slot) }, /* req_key_slot */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_s_resp_key_create, .offset = offsetof(struct s_cmd_key_create, resp) }, /* resp */
};

struct caut_field const record_fields_helium_atom_api_s_resp_lstat[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_status, .offset = offsetof(struct s_resp_lstat, status) }, /* status */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_s_lstat, .offset = offsetof(struct s_resp_lstat, lstat) }, /* lstat */
};

struct caut_field const union_fields_helium_atom_api_s_cmd_read_lstat[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_s_resp_lstat, .offset = offsetof(struct s_cmd_read_lstat, resp) }, /* resp */
};

struct caut_field const record_fields_helium_atom_api_s_resp_part[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_status, .offset = offsetof(struct s_resp_part, status) }, /* status */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_s_part_num, .offset = offsetof(struct s_resp_part, sec_part_num) }, /* sec_part_num */
};

struct caut_field const union_fields_helium_atom_api_s_cmd_read_part[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_s_resp_part, .offset = offsetof(struct s_cmd_read_part, resp) }, /* resp */
};

struct caut_field const record_fields_helium_atom_api_a_resp_u8[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_status, .offset = offsetof(struct a_resp_u8, status) }, /* status */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct a_resp_u8, value) }, /* value */
};

struct caut_field const record_fields_helium_atom_api_a_resp_u64[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_status, .offset = offsetof(struct a_resp_u64, status) }, /* status */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_u64, .offset = offsetof(struct a_resp_u64, value) }, /* value */
};

struct caut_field const record_fields_helium_atom_api_a_resp_sleep_mode[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_status, .offset = offsetof(struct a_resp_sleep_mode, status) }, /* status */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_sleep_mode, .offset = offsetof(struct a_resp_sleep_mode, sleep_mode) }, /* sleep_mode */
};

struct caut_field const record_fields_helium_atom_api_a_resp_mfg_data[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_status, .offset = offsetof(struct a_resp_mfg_data, status) }, /* status */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_h_mfg_data, .offset = offsetof(struct a_resp_mfg_data, value) }, /* value */
};

struct caut_field const record_fields_helium_atom_api_a_resp_get_atom_info[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_status, .offset = offsetof(struct a_resp_get_atom_info, status) }, /* status */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct a_resp_get_atom_info, radio_count) }, /* radio_count */
  { .field_index = 2, .data = true, .ref_id = type_id_helium_atom_api_u32, .offset = offsetof(struct a_resp_get_atom_info, uptime) }, /* uptime */
  { .field_index = 3, .data = true, .ref_id = type_id_helium_atom_api_a_time, .offset = offsetof(struct a_resp_get_atom_info, time) }, /* time */
  { .field_index = 4, .data = true, .ref_id = type_id_helium_atom_api_a_version, .offset = offsetof(struct a_resp_get_atom_info, fw_version) }, /* fw_version */
  { .field_index = 5, .data = true, .ref_id = type_id_helium_atom_api_h_buf_20b, .offset = offsetof(struct a_resp_get_atom_info, schema_fp) }, /* schema_fp */
};

struct caut_field const record_fields_helium_atom_api_a_resp_gen[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_status, .offset = offsetof(struct a_resp_gen, status) }, /* status */
};

struct caut_field const union_fields_helium_atom_api_n_cmd_set_mode[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_n_mode, .offset = offsetof(struct n_cmd_set_mode, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct n_cmd_set_mode, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_r_cmd_beacon[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_beacon_cmd, .offset = offsetof(struct r_cmd_beacon, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct r_cmd_beacon, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_r_cmd_pan[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_pan_cmd, .offset = offsetof(struct r_cmd_pan, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct r_cmd_pan, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_r_cmd_pan_fr[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_pan_frame, .offset = offsetof(struct r_cmd_pan_fr, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct r_cmd_pan_fr, resp) }, /* resp */
};

struct caut_field const record_fields_helium_atom_api_r_cmd_power[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_power_cmd, .offset = offsetof(struct r_cmd_power, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct r_cmd_power, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_r_cmd_scan_start[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct r_cmd_scan_start, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_r_cmd_set_chan[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct r_cmd_set_chan, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct r_cmd_set_chan, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_r_cmd_set_pan_id[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u16, .offset = offsetof(struct r_cmd_set_pan_id, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct r_cmd_set_pan_id, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_r_cmd_set_sh_addr[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u16, .offset = offsetof(struct r_cmd_set_sh_addr, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct r_cmd_set_sh_addr, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_s_cmd_init[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct s_cmd_init, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_s_cmd_key_update[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_s_key_update_req, .offset = offsetof(struct s_cmd_key_update, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct s_cmd_key_update, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_s_cmd_lock[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct s_cmd_lock, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_r_cmd_get_info[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_radio_type, .offset = offsetof(struct r_cmd_get_info, req_rtype) }, /* req_rtype */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_r_cmd_get_info_resp, .offset = offsetof(struct r_cmd_get_info, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_r_cmd[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_r_cmd_scan_start, .offset = offsetof(struct r_cmd, scan_start) }, /* scan_start */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_r_cmd_set_pan_id, .offset = offsetof(struct r_cmd, set_pan_id) }, /* set_pan_id */
  { .field_index = 2, .data = true, .ref_id = type_id_helium_atom_api_r_cmd_set_sh_addr, .offset = offsetof(struct r_cmd, set_sh_addr) }, /* set_sh_addr */
  { .field_index = 3, .data = true, .ref_id = type_id_helium_atom_api_r_cmd_set_chan, .offset = offsetof(struct r_cmd, set_channel) }, /* set_channel */
  { .field_index = 4, .data = true, .ref_id = type_id_helium_atom_api_r_cmd_pan, .offset = offsetof(struct r_cmd, pan) }, /* pan */
  { .field_index = 5, .data = true, .ref_id = type_id_helium_atom_api_r_cmd_beacon, .offset = offsetof(struct r_cmd, beacon) }, /* beacon */
  { .field_index = 6, .data = true, .ref_id = type_id_helium_atom_api_r_cmd_pan_fr, .offset = offsetof(struct r_cmd, pan_fr) }, /* pan_fr */
  { .field_index = 7, .data = true, .ref_id = type_id_helium_atom_api_r_cmd_power, .offset = offsetof(struct r_cmd, power) }, /* power */
  { .field_index = 8, .data = true, .ref_id = type_id_helium_atom_api_r_cmd_get_info, .offset = offsetof(struct r_cmd, get_info) }, /* get_info */
};

struct caut_field const record_fields_helium_atom_api_a_data[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_h_buf, .offset = offsetof(struct a_data, buf) }, /* buf */
};

struct caut_field const union_fields_helium_atom_api_n_poll_data[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* none */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_data, .offset = offsetof(struct n_poll_data, frame) }, /* frame */
  { .field_index = 2, .data = false, .ref_id = 0, .offset = 0 }, /* err_not_autonomous */
  { .field_index = 3, .data = false, .ref_id = 0, .offset = 0 }, /* need_reset */
};

struct caut_field const record_fields_helium_atom_api_n_cmd_poll_data_resp[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u32, .offset = offsetof(struct n_cmd_poll_data_resp, frames_droped) }, /* frames_droped */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_n_poll_data, .offset = offsetof(struct n_cmd_poll_data_resp, poll_data) }, /* poll_data */
};

struct caut_field const union_fields_helium_atom_api_n_cmd_poll_data[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_poll_data_resp, .offset = offsetof(struct n_cmd_poll_data, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_security[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_s_cmd_read_part, .offset = offsetof(struct a_cmd_security, read_part) }, /* read_part */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_s_cmd_init, .offset = offsetof(struct a_cmd_security, init) }, /* init */
  { .field_index = 2, .data = true, .ref_id = type_id_helium_atom_api_s_cmd_read_lstat, .offset = offsetof(struct a_cmd_security, read_lstat) }, /* read_lstat */
  { .field_index = 3, .data = true, .ref_id = type_id_helium_atom_api_s_cmd_key_create, .offset = offsetof(struct a_cmd_security, key_create) }, /* key_create */
  { .field_index = 4, .data = true, .ref_id = type_id_helium_atom_api_s_cmd_key_update, .offset = offsetof(struct a_cmd_security, key_update) }, /* key_update */
  { .field_index = 5, .data = true, .ref_id = type_id_helium_atom_api_s_cmd_lock, .offset = offsetof(struct a_cmd_security, lock) }, /* lock */
  { .field_index = 6, .data = true, .ref_id = type_id_helium_atom_api_s_cmd_key_sigs, .offset = offsetof(struct a_cmd_security, get_key_sigs) }, /* get_key_sigs */
  { .field_index = 7, .data = true, .ref_id = type_id_helium_atom_api_s_cmd_gen_session_key, .offset = offsetof(struct a_cmd_security, gen_session_key) }, /* gen_session_key */
};

struct caut_field const record_fields_helium_atom_api_a_cmd_radio[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_radio_type, .offset = offsetof(struct a_cmd_radio, radio_id) }, /* radio_id */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_r_cmd, .offset = offsetof(struct a_cmd_radio, cmd) }, /* cmd */
};

struct caut_field const record_fields_helium_atom_api_a_cmd_pin[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct a_cmd_pin, pin_num) }, /* pin_num */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_node[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_set_mode, .offset = offsetof(struct a_cmd_node, set_mode) }, /* set_mode */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_get_mode, .offset = offsetof(struct a_cmd_node, get_mode) }, /* get_mode */
  { .field_index = 2, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_reflash_header, .offset = offsetof(struct a_cmd_node, reflash_header) }, /* reflash_header */
  { .field_index = 3, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_reflash_data, .offset = offsetof(struct a_cmd_node, reflash_data) }, /* reflash_data */
  { .field_index = 4, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_send, .offset = offsetof(struct a_cmd_node, send) }, /* send */
  { .field_index = 5, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_connection_status, .offset = offsetof(struct a_cmd_node, connection_status) }, /* connection_status */
  { .field_index = 6, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_poll_data, .offset = offsetof(struct a_cmd_node, poll_data) }, /* poll_data */
  { .field_index = 7, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_connect, .offset = offsetof(struct a_cmd_node, connect) }, /* connect */
  { .field_index = 8, .data = true, .ref_id = type_id_helium_atom_api_n_cmd_sleep, .offset = offsetof(struct a_cmd_node, sleep) }, /* sleep */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_config_set_time[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_time, .offset = offsetof(struct a_cmd_config_set_time, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct a_cmd_config_set_time, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_config_set_sleep_mode[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_sleep_mode, .offset = offsetof(struct a_cmd_config_set_sleep_mode, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct a_cmd_config_set_sleep_mode, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_config_set_op_mode[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_op_mode, .offset = offsetof(struct a_cmd_config_set_op_mode, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct a_cmd_config_set_op_mode, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_config_set_mfg_data[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_h_mfg_data, .offset = offsetof(struct a_cmd_config_set_mfg_data, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct a_cmd_config_set_mfg_data, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_config_set_mac[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_h_mac, .offset = offsetof(struct a_cmd_config_set_mac, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct a_cmd_config_set_mac, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_config_read_sleep_mode[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_sleep_mode, .offset = offsetof(struct a_cmd_config_read_sleep_mode, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_config_read_mfg_data[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_mfg_data, .offset = offsetof(struct a_cmd_config_read_mfg_data, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_config_read_mac[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_u64, .offset = offsetof(struct a_cmd_config_read_mac, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_config_get_atom_info[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_get_atom_info, .offset = offsetof(struct a_cmd_config_get_atom_info, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_brd_reset[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct a_cmd_brd_reset, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_brd_pin_out[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_pin, .offset = offsetof(struct a_cmd_brd_pin_out, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct a_cmd_brd_pin_out, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_brd_pin_in[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_pin, .offset = offsetof(struct a_cmd_brd_pin_in, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_u8, .offset = offsetof(struct a_cmd_brd_pin_in, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_board[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_brd_reset, .offset = offsetof(struct a_cmd_board, reset) }, /* reset */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_brd_pin_out, .offset = offsetof(struct a_cmd_board, pin_set) }, /* pin_set */
  { .field_index = 2, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_brd_pin_out, .offset = offsetof(struct a_cmd_board, pin_clear) }, /* pin_clear */
  { .field_index = 3, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_brd_pin_in, .offset = offsetof(struct a_cmd_board, pin_read) }, /* pin_read */
};

struct caut_field const record_fields_helium_atom_api_a_channel_report[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct a_channel_report, channel) }, /* channel */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_u16, .offset = offsetof(struct a_channel_report, energy) }, /* energy */
};

struct caut_field const record_fields_helium_atom_api_a_beacon_report[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u16, .offset = offsetof(struct a_beacon_report, pan_id) }, /* pan_id */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_u16, .offset = offsetof(struct a_beacon_report, short_addr) }, /* short_addr */
  { .field_index = 2, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct a_beacon_report, lqi) }, /* lqi */
  { .field_index = 3, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct a_beacon_report, ed) }, /* ed */
  { .field_index = 4, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct a_beacon_report, channel) }, /* channel */
  { .field_index = 5, .data = true, .ref_id = type_id_helium_atom_api_u32, .offset = offsetof(struct a_beacon_report, time) }, /* time */
};

struct caut_field const record_fields_helium_atom_api_a_scan_report[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u8, .offset = offsetof(struct a_scan_report, radio_index) }, /* radio_index */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_channel_reports, .offset = offsetof(struct a_scan_report, channels) }, /* channels */
  { .field_index = 2, .data = true, .ref_id = type_id_helium_atom_api_a_beacon_reports, .offset = offsetof(struct a_scan_report, beacons) }, /* beacons */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_config_read_baud_rate[] = {
  { .field_index = 0, .data = false, .ref_id = 0, .offset = 0 }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_baud_rate, .offset = offsetof(struct a_cmd_config_read_baud_rate, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_config_set_baud_rate[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_baud_rate, .offset = offsetof(struct a_cmd_config_set_baud_rate, req) }, /* req */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_resp_gen, .offset = offsetof(struct a_cmd_config_set_baud_rate, resp) }, /* resp */
};

struct caut_field const union_fields_helium_atom_api_a_cmd_config[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_config_set_op_mode, .offset = offsetof(struct a_cmd_config, set_op_mode) }, /* set_op_mode */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_config_set_mac, .offset = offsetof(struct a_cmd_config, set_mac) }, /* set_mac */
  { .field_index = 2, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_config_read_mac, .offset = offsetof(struct a_cmd_config, read_mac) }, /* read_mac */
  { .field_index = 3, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_config_set_mfg_data, .offset = offsetof(struct a_cmd_config, set_mfg_data) }, /* set_mfg_data */
  { .field_index = 4, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_config_read_mfg_data, .offset = offsetof(struct a_cmd_config, read_mfg_data) }, /* read_mfg_data */
  { .field_index = 5, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_config_set_sleep_mode, .offset = offsetof(struct a_cmd_config, set_sleep_mode) }, /* set_sleep_mode */
  { .field_index = 6, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_config_read_sleep_mode, .offset = offsetof(struct a_cmd_config, read_sleep_mode) }, /* read_sleep_mode */
  { .field_index = 7, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_config_set_baud_rate, .offset = offsetof(struct a_cmd_config, set_baud_rate) }, /* set_baud_rate */
  { .field_index = 8, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_config_read_baud_rate, .offset = offsetof(struct a_cmd_config, read_baud_rate) }, /* read_baud_rate */
  { .field_index = 9, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_config_set_time, .offset = offsetof(struct a_cmd_config, set_time) }, /* set_time */
  { .field_index = 10, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_config_get_atom_info, .offset = offsetof(struct a_cmd_config, get_atom_info) }, /* get_atom_info */
};

struct caut_field const union_fields_helium_atom_api_a_cmd[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_board, .offset = offsetof(struct a_cmd, board_cmd) }, /* board_cmd */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_config, .offset = offsetof(struct a_cmd, config_cmd) }, /* config_cmd */
  { .field_index = 2, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_security, .offset = offsetof(struct a_cmd, security_cmd) }, /* security_cmd */
  { .field_index = 3, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_radio, .offset = offsetof(struct a_cmd, radio_cmd) }, /* radio_cmd */
  { .field_index = 4, .data = true, .ref_id = type_id_helium_atom_api_a_data, .offset = offsetof(struct a_cmd, data) }, /* data */
  { .field_index = 5, .data = true, .ref_id = type_id_helium_atom_api_a_scan_report, .offset = offsetof(struct a_cmd, scan_report) }, /* scan_report */
  { .field_index = 6, .data = true, .ref_id = type_id_helium_atom_api_a_debug_msg, .offset = offsetof(struct a_cmd, debug) }, /* debug */
  { .field_index = 7, .data = true, .ref_id = type_id_helium_atom_api_a_cmd_node, .offset = offsetof(struct a_cmd, node_cmd) }, /* node_cmd */
};

struct caut_field const record_fields_helium_atom_api_a_cmd_t[] = {
  { .field_index = 0, .data = true, .ref_id = type_id_helium_atom_api_u16, .offset = offsetof(struct a_cmd_t, sequence) }, /* sequence */
  { .field_index = 1, .data = true, .ref_id = type_id_helium_atom_api_a_cmd, .offset = offsetof(struct a_cmd_t, cmd) }, /* cmd */
};


struct type_descriptor const type_descriptors_helium_atom_api[TYPE_COUNT_helium_atom_api] = {
  { /* s_ssk */
    .type_id = type_id_helium_atom_api_s_ssk,
    .obj_size = sizeof(struct s_ssk),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_u8,
      .max_length = 32u,
      .tag = caut_tag_8,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
      .elem_offset = offsetof(struct s_ssk, elems),
    },
  },
  { /* s_sig */
    .type_id = type_id_helium_atom_api_s_sig,
    .obj_size = sizeof(struct s_sig),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_u8,
      .max_length = 8u,
      .tag = caut_tag_8,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
      .elem_offset = offsetof(struct s_sig, elems),
    },
  },
  { /* s_sigs */
    .type_id = type_id_helium_atom_api_s_sigs,
    .obj_size = sizeof(struct s_sigs),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_s_sig,
      .max_length = 8u,
      .tag = caut_tag_8,
      .elem_span = ARR_ELEM_SPAN(struct s_sig),
      .elem_offset = offsetof(struct s_sigs, elems),
    },
  },
  { /* s_sec_type */
    .type_id = type_id_helium_atom_api_s_sec_type,
    .obj_size = sizeof(enum s_sec_type),
    .prototype_tag = caut_proto_enumeration,
    .prototype.c_enumeration = {
      .tag = caut_tag_8,
      .length = 2u,
    },
  },
  { /* s_part_num */
    .type_id = type_id_helium_atom_api_s_part_num,
    .obj_size = sizeof(struct s_part_num),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_u8,
      .max_length = 13u,
      .tag = caut_tag_8,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
      .elem_offset = offsetof(struct s_part_num, elems),
    },
  },
  { /* s_lstat */
    .type_id = type_id_helium_atom_api_s_lstat,
    .obj_size = sizeof(enum s_lstat),
    .prototype_tag = caut_proto_enumeration,
    .prototype.c_enumeration = {
      .tag = caut_tag_8,
      .length = 4u,
    },
  },
  { /* s_key_sigs */
    .type_id = type_id_helium_atom_api_s_key_sigs,
    .obj_size = sizeof(struct s_key_sigs),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_u8,
      .max_length = 69u,
      .tag = caut_tag_8,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
      .elem_offset = offsetof(struct s_key_sigs, elems),
    },
  },
  { /* s_key_sig_req */
    .type_id = type_id_helium_atom_api_s_key_sig_req,
    .obj_size = sizeof(struct s_key_sig_req),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_u8,
      .max_length = 37u,
      .tag = caut_tag_8,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
      .elem_offset = offsetof(struct s_key_sig_req, elems),
    },
  },
  { /* s_key_sig_req_rec */
    .type_id = type_id_helium_atom_api_s_key_sig_req_rec,
    .obj_size = sizeof(struct s_key_sig_req_rec),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_s_key_sig_req_rec,
    },
  },
  { /* s_gen_session_key_req */
    .type_id = type_id_helium_atom_api_s_gen_session_key_req,
    .obj_size = sizeof(struct s_gen_session_key_req),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_s_gen_session_key_req,
    },
  },
  { /* power_cmd */
    .type_id = type_id_helium_atom_api_power_cmd,
    .obj_size = sizeof(enum power_cmd),
    .prototype_tag = caut_proto_enumeration,
    .prototype.c_enumeration = {
      .tag = caut_tag_8,
      .length = 2u,
    },
  },
  { /* pan_frame */
    .type_id = type_id_helium_atom_api_pan_frame,
    .obj_size = sizeof(struct pan_frame),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_u8,
      .max_length = 107u,
      .tag = caut_tag_8,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
      .elem_offset = offsetof(struct pan_frame, elems),
    },
  },
  { /* pan_cmd */
    .type_id = type_id_helium_atom_api_pan_cmd,
    .obj_size = sizeof(enum pan_cmd),
    .prototype_tag = caut_proto_enumeration,
    .prototype.c_enumeration = {
      .tag = caut_tag_8,
      .length = 2u,
    },
  },
  { /* n_send_tx_status */
    .type_id = type_id_helium_atom_api_n_send_tx_status,
    .obj_size = sizeof(enum n_send_tx_status),
    .prototype_tag = caut_proto_enumeration,
    .prototype.c_enumeration = {
      .tag = caut_tag_8,
      .length = 3u,
    },
  },
  { /* n_send_req */
    .type_id = type_id_helium_atom_api_n_send_req,
    .obj_size = sizeof(struct n_send_req),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 1u,
      .fields = record_fields_helium_atom_api_n_send_req,
    },
  },
  { /* n_send_metadata */
    .type_id = type_id_helium_atom_api_n_send_metadata,
    .obj_size = sizeof(struct n_send_metadata),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 1u,
      .fields = record_fields_helium_atom_api_n_send_metadata,
    },
  },
  { /* n_send_err */
    .type_id = type_id_helium_atom_api_n_send_err,
    .obj_size = sizeof(enum n_send_err),
    .prototype_tag = caut_proto_enumeration,
    .prototype.c_enumeration = {
      .tag = caut_tag_8,
      .length = 5u,
    },
  },
  { /* n_send_resp */
    .type_id = type_id_helium_atom_api_n_send_resp,
    .obj_size = sizeof(struct n_send_resp),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_n_send_resp,
    },
  },
  { /* n_mode */
    .type_id = type_id_helium_atom_api_n_mode,
    .obj_size = sizeof(enum n_mode),
    .prototype_tag = caut_proto_enumeration,
    .prototype.c_enumeration = {
      .tag = caut_tag_8,
      .length = 2u,
    },
  },
  { /* n_img_sha */
    .type_id = type_id_helium_atom_api_n_img_sha,
    .obj_size = sizeof(struct n_img_sha),
    .prototype_tag = caut_proto_array,
    .prototype.c_array = {
      .ref_id = type_id_helium_atom_api_u8,
      .length = 32u,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
    },
  },
  { /* n_reflash_header */
    .type_id = type_id_helium_atom_api_n_reflash_header,
    .obj_size = sizeof(struct n_reflash_header),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_n_reflash_header,
    },
  },
  { /* n_img_id */
    .type_id = type_id_helium_atom_api_n_img_id,
    .obj_size = sizeof(struct n_img_id),
    .prototype_tag = caut_proto_array,
    .prototype.c_array = {
      .ref_id = type_id_helium_atom_api_u8,
      .length = 4u,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
    },
  },
  { /* n_img_data */
    .type_id = type_id_helium_atom_api_n_img_data,
    .obj_size = sizeof(struct n_img_data),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_u8,
      .max_length = 256u,
      .tag = caut_tag_16,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
      .elem_offset = offsetof(struct n_img_data, elems),
    },
  },
  { /* n_reflash_data */
    .type_id = type_id_helium_atom_api_n_reflash_data,
    .obj_size = sizeof(struct n_reflash_data),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 3u,
      .fields = record_fields_helium_atom_api_n_reflash_data,
    },
  },
  { /* n_cmd_send */
    .type_id = type_id_helium_atom_api_n_cmd_send,
    .obj_size = sizeof(struct n_cmd_send),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_n_cmd_send,
    },
  },
  { /* n_cmd_reflash_header_resp */
    .type_id = type_id_helium_atom_api_n_cmd_reflash_header_resp,
    .obj_size = sizeof(enum n_cmd_reflash_header_resp),
    .prototype_tag = caut_proto_enumeration,
    .prototype.c_enumeration = {
      .tag = caut_tag_8,
      .length = 3u,
    },
  },
  { /* n_cmd_reflash_header */
    .type_id = type_id_helium_atom_api_n_cmd_reflash_header,
    .obj_size = sizeof(struct n_cmd_reflash_header),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_n_cmd_reflash_header,
    },
  },
  { /* n_cmd_reflash_data_resp */
    .type_id = type_id_helium_atom_api_n_cmd_reflash_data_resp,
    .obj_size = sizeof(struct n_cmd_reflash_data_resp),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 6u,
      .fields = union_fields_helium_atom_api_n_cmd_reflash_data_resp,
    },
  },
  { /* n_cmd_reflash_data */
    .type_id = type_id_helium_atom_api_n_cmd_reflash_data,
    .obj_size = sizeof(struct n_cmd_reflash_data),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_n_cmd_reflash_data,
    },
  },
  { /* n_cmd_get_mode */
    .type_id = type_id_helium_atom_api_n_cmd_get_mode,
    .obj_size = sizeof(struct n_cmd_get_mode),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_n_cmd_get_mode,
    },
  },
  { /* n_cmd_connection_status_resp */
    .type_id = type_id_helium_atom_api_n_cmd_connection_status_resp,
    .obj_size = sizeof(struct n_cmd_connection_status_resp),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 1u,
      .fields = record_fields_helium_atom_api_n_cmd_connection_status_resp,
    },
  },
  { /* n_cmd_connection_status */
    .type_id = type_id_helium_atom_api_n_cmd_connection_status,
    .obj_size = sizeof(struct n_cmd_connection_status),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_n_cmd_connection_status,
    },
  },
  { /* n_cmd_connect_resp */
    .type_id = type_id_helium_atom_api_n_cmd_connect_resp,
    .obj_size = sizeof(enum n_cmd_connect_resp),
    .prototype_tag = caut_proto_enumeration,
    .prototype.c_enumeration = {
      .tag = caut_tag_8,
      .length = 3u,
    },
  },
  { /* h_scan */
    .type_id = type_id_helium_atom_api_h_scan,
    .obj_size = sizeof(struct h_scan),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_u8,
      .max_length = 64u,
      .tag = caut_tag_8,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
      .elem_offset = offsetof(struct h_scan, elems),
    },
  },
  { /* h_mfg_data */
    .type_id = type_id_helium_atom_api_h_mfg_data,
    .obj_size = sizeof(struct h_mfg_data),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_u8,
      .max_length = 32u,
      .tag = caut_tag_8,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
      .elem_offset = offsetof(struct h_mfg_data, elems),
    },
  },
  { /* h_mac */
    .type_id = type_id_helium_atom_api_h_mac,
    .obj_size = sizeof(h_mac),
    .prototype_tag = caut_proto_synonym,
    .prototype.c_synonym = {
      .ref_id = type_id_helium_atom_api_u64,
    },
  },
  { /* s_get_derived_key_req */
    .type_id = type_id_helium_atom_api_s_get_derived_key_req,
    .obj_size = sizeof(struct s_get_derived_key_req),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_s_get_derived_key_req,
    },
  },
  { /* h_data_u8 */
    .type_id = type_id_helium_atom_api_h_data_u8,
    .obj_size = sizeof(h_data_u8),
    .prototype_tag = caut_proto_synonym,
    .prototype.c_synonym = {
      .ref_id = type_id_helium_atom_api_u8,
    },
  },
  { /* h_data_u32 */
    .type_id = type_id_helium_atom_api_h_data_u32,
    .obj_size = sizeof(h_data_u32),
    .prototype_tag = caut_proto_synonym,
    .prototype.c_synonym = {
      .ref_id = type_id_helium_atom_api_u32,
    },
  },
  { /* h_data_u16 */
    .type_id = type_id_helium_atom_api_h_data_u16,
    .obj_size = sizeof(h_data_u16),
    .prototype_tag = caut_proto_synonym,
    .prototype.c_synonym = {
      .ref_id = type_id_helium_atom_api_u16,
    },
  },
  { /* h_buf_32b */
    .type_id = type_id_helium_atom_api_h_buf_32b,
    .obj_size = sizeof(struct h_buf_32b),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_u8,
      .max_length = 32u,
      .tag = caut_tag_8,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
      .elem_offset = offsetof(struct h_buf_32b, elems),
    },
  },
  { /* s_key_update_req */
    .type_id = type_id_helium_atom_api_s_key_update_req,
    .obj_size = sizeof(struct s_key_update_req),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 3u,
      .fields = record_fields_helium_atom_api_s_key_update_req,
    },
  },
  { /* h_buf_20b */
    .type_id = type_id_helium_atom_api_h_buf_20b,
    .obj_size = sizeof(struct h_buf_20b),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_u8,
      .max_length = 20u,
      .tag = caut_tag_8,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
      .elem_offset = offsetof(struct h_buf_20b, elems),
    },
  },
  { /* h_buf */
    .type_id = type_id_helium_atom_api_h_buf,
    .obj_size = sizeof(struct h_buf),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_u8,
      .max_length = 128u,
      .tag = caut_tag_8,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
      .elem_offset = offsetof(struct h_buf, elems),
    },
  },
  { /* h_arr_32b */
    .type_id = type_id_helium_atom_api_h_arr_32b,
    .obj_size = sizeof(struct h_arr_32b),
    .prototype_tag = caut_proto_array,
    .prototype.c_array = {
      .ref_id = type_id_helium_atom_api_u8,
      .length = 32u,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
    },
  },
  { /* beacon_cmd */
    .type_id = type_id_helium_atom_api_beacon_cmd,
    .obj_size = sizeof(enum beacon_cmd),
    .prototype_tag = caut_proto_enumeration,
    .prototype.c_enumeration = {
      .tag = caut_tag_8,
      .length = 2u,
    },
  },
  { /* a_version */
    .type_id = type_id_helium_atom_api_a_version,
    .obj_size = sizeof(struct a_version),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 4u,
      .fields = record_fields_helium_atom_api_a_version,
    },
  },
  { /* n_connection */
    .type_id = type_id_helium_atom_api_n_connection,
    .obj_size = sizeof(struct n_connection),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 12u,
      .fields = record_fields_helium_atom_api_n_connection,
    },
  },
  { /* n_cmd_sleep_resp */
    .type_id = type_id_helium_atom_api_n_cmd_sleep_resp,
    .obj_size = sizeof(struct n_cmd_sleep_resp),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 5u,
      .fields = union_fields_helium_atom_api_n_cmd_sleep_resp,
    },
  },
  { /* n_cmd_sleep */
    .type_id = type_id_helium_atom_api_n_cmd_sleep,
    .obj_size = sizeof(struct n_cmd_sleep),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_n_cmd_sleep,
    },
  },
  { /* n_connection_quick */
    .type_id = type_id_helium_atom_api_n_connection_quick,
    .obj_size = sizeof(struct n_connection_quick),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_n_connection_quick,
    },
  },
  { /* n_cmd_connect_req */
    .type_id = type_id_helium_atom_api_n_cmd_connect_req,
    .obj_size = sizeof(struct n_cmd_connect_req),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_n_cmd_connect_req,
    },
  },
  { /* n_cmd_connect */
    .type_id = type_id_helium_atom_api_n_cmd_connect,
    .obj_size = sizeof(struct n_cmd_connect),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_n_cmd_connect,
    },
  },
  { /* a_time */
    .type_id = type_id_helium_atom_api_a_time,
    .obj_size = sizeof(struct a_time),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_a_time,
    },
  },
  { /* a_status */
    .type_id = type_id_helium_atom_api_a_status,
    .obj_size = sizeof(enum a_status),
    .prototype_tag = caut_proto_enumeration,
    .prototype.c_enumeration = {
      .tag = caut_tag_8,
      .length = 2u,
    },
  },
  { /* r_cmd_get_info_resp */
    .type_id = type_id_helium_atom_api_r_cmd_get_info_resp,
    .obj_size = sizeof(struct r_cmd_get_info_resp),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 8u,
      .fields = record_fields_helium_atom_api_r_cmd_get_info_resp,
    },
  },
  { /* s_gen_session_key_resp */
    .type_id = type_id_helium_atom_api_s_gen_session_key_resp,
    .obj_size = sizeof(struct s_gen_session_key_resp),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_s_gen_session_key_resp,
    },
  },
  { /* s_cmd_gen_session_key */
    .type_id = type_id_helium_atom_api_s_cmd_gen_session_key,
    .obj_size = sizeof(struct s_cmd_gen_session_key),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_s_cmd_gen_session_key,
    },
  },
  { /* s_get_derived_key_resp */
    .type_id = type_id_helium_atom_api_s_get_derived_key_resp,
    .obj_size = sizeof(struct s_get_derived_key_resp),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_s_get_derived_key_resp,
    },
  },
  { /* s_cmd_get_derived_key */
    .type_id = type_id_helium_atom_api_s_cmd_get_derived_key,
    .obj_size = sizeof(struct s_cmd_get_derived_key),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_s_cmd_get_derived_key,
    },
  },
  { /* s_key_sig_resp */
    .type_id = type_id_helium_atom_api_s_key_sig_resp,
    .obj_size = sizeof(struct s_key_sig_resp),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_s_key_sig_resp,
    },
  },
  { /* s_cmd_key_sigs */
    .type_id = type_id_helium_atom_api_s_cmd_key_sigs,
    .obj_size = sizeof(struct s_cmd_key_sigs),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_s_cmd_key_sigs,
    },
  },
  { /* s_resp_key_create */
    .type_id = type_id_helium_atom_api_s_resp_key_create,
    .obj_size = sizeof(struct s_resp_key_create),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 3u,
      .fields = record_fields_helium_atom_api_s_resp_key_create,
    },
  },
  { /* s_cmd_key_create */
    .type_id = type_id_helium_atom_api_s_cmd_key_create,
    .obj_size = sizeof(struct s_cmd_key_create),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_s_cmd_key_create,
    },
  },
  { /* s_resp_lstat */
    .type_id = type_id_helium_atom_api_s_resp_lstat,
    .obj_size = sizeof(struct s_resp_lstat),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_s_resp_lstat,
    },
  },
  { /* s_cmd_read_lstat */
    .type_id = type_id_helium_atom_api_s_cmd_read_lstat,
    .obj_size = sizeof(struct s_cmd_read_lstat),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_s_cmd_read_lstat,
    },
  },
  { /* s_resp_part */
    .type_id = type_id_helium_atom_api_s_resp_part,
    .obj_size = sizeof(struct s_resp_part),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_s_resp_part,
    },
  },
  { /* s_cmd_read_part */
    .type_id = type_id_helium_atom_api_s_cmd_read_part,
    .obj_size = sizeof(struct s_cmd_read_part),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_s_cmd_read_part,
    },
  },
  { /* a_sleep_mode */
    .type_id = type_id_helium_atom_api_a_sleep_mode,
    .obj_size = sizeof(enum a_sleep_mode),
    .prototype_tag = caut_proto_enumeration,
    .prototype.c_enumeration = {
      .tag = caut_tag_8,
      .length = 2u,
    },
  },
  { /* a_resp_u8 */
    .type_id = type_id_helium_atom_api_a_resp_u8,
    .obj_size = sizeof(struct a_resp_u8),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_a_resp_u8,
    },
  },
  { /* a_resp_u64 */
    .type_id = type_id_helium_atom_api_a_resp_u64,
    .obj_size = sizeof(struct a_resp_u64),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_a_resp_u64,
    },
  },
  { /* a_resp_sleep_mode */
    .type_id = type_id_helium_atom_api_a_resp_sleep_mode,
    .obj_size = sizeof(struct a_resp_sleep_mode),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_a_resp_sleep_mode,
    },
  },
  { /* a_resp_mfg_data */
    .type_id = type_id_helium_atom_api_a_resp_mfg_data,
    .obj_size = sizeof(struct a_resp_mfg_data),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_a_resp_mfg_data,
    },
  },
  { /* a_resp_get_atom_info */
    .type_id = type_id_helium_atom_api_a_resp_get_atom_info,
    .obj_size = sizeof(struct a_resp_get_atom_info),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 6u,
      .fields = record_fields_helium_atom_api_a_resp_get_atom_info,
    },
  },
  { /* a_resp_gen */
    .type_id = type_id_helium_atom_api_a_resp_gen,
    .obj_size = sizeof(struct a_resp_gen),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 1u,
      .fields = record_fields_helium_atom_api_a_resp_gen,
    },
  },
  { /* n_cmd_set_mode */
    .type_id = type_id_helium_atom_api_n_cmd_set_mode,
    .obj_size = sizeof(struct n_cmd_set_mode),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_n_cmd_set_mode,
    },
  },
  { /* r_cmd_beacon */
    .type_id = type_id_helium_atom_api_r_cmd_beacon,
    .obj_size = sizeof(struct r_cmd_beacon),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_r_cmd_beacon,
    },
  },
  { /* r_cmd_pan */
    .type_id = type_id_helium_atom_api_r_cmd_pan,
    .obj_size = sizeof(struct r_cmd_pan),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_r_cmd_pan,
    },
  },
  { /* r_cmd_pan_fr */
    .type_id = type_id_helium_atom_api_r_cmd_pan_fr,
    .obj_size = sizeof(struct r_cmd_pan_fr),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_r_cmd_pan_fr,
    },
  },
  { /* r_cmd_power */
    .type_id = type_id_helium_atom_api_r_cmd_power,
    .obj_size = sizeof(struct r_cmd_power),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_r_cmd_power,
    },
  },
  { /* r_cmd_scan_start */
    .type_id = type_id_helium_atom_api_r_cmd_scan_start,
    .obj_size = sizeof(struct r_cmd_scan_start),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_r_cmd_scan_start,
    },
  },
  { /* r_cmd_set_chan */
    .type_id = type_id_helium_atom_api_r_cmd_set_chan,
    .obj_size = sizeof(struct r_cmd_set_chan),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_r_cmd_set_chan,
    },
  },
  { /* r_cmd_set_pan_id */
    .type_id = type_id_helium_atom_api_r_cmd_set_pan_id,
    .obj_size = sizeof(struct r_cmd_set_pan_id),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_r_cmd_set_pan_id,
    },
  },
  { /* r_cmd_set_sh_addr */
    .type_id = type_id_helium_atom_api_r_cmd_set_sh_addr,
    .obj_size = sizeof(struct r_cmd_set_sh_addr),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_r_cmd_set_sh_addr,
    },
  },
  { /* s_cmd_init */
    .type_id = type_id_helium_atom_api_s_cmd_init,
    .obj_size = sizeof(struct s_cmd_init),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_s_cmd_init,
    },
  },
  { /* s_cmd_key_update */
    .type_id = type_id_helium_atom_api_s_cmd_key_update,
    .obj_size = sizeof(struct s_cmd_key_update),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_s_cmd_key_update,
    },
  },
  { /* s_cmd_lock */
    .type_id = type_id_helium_atom_api_s_cmd_lock,
    .obj_size = sizeof(struct s_cmd_lock),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_s_cmd_lock,
    },
  },
  { /* a_radio_type */
    .type_id = type_id_helium_atom_api_a_radio_type,
    .obj_size = sizeof(enum a_radio_type),
    .prototype_tag = caut_proto_enumeration,
    .prototype.c_enumeration = {
      .tag = caut_tag_8,
      .length = 2u,
    },
  },
  { /* r_cmd_get_info */
    .type_id = type_id_helium_atom_api_r_cmd_get_info,
    .obj_size = sizeof(struct r_cmd_get_info),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_r_cmd_get_info,
    },
  },
  { /* r_cmd */
    .type_id = type_id_helium_atom_api_r_cmd,
    .obj_size = sizeof(struct r_cmd),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 9u,
      .fields = union_fields_helium_atom_api_r_cmd,
    },
  },
  { /* a_op_mode */
    .type_id = type_id_helium_atom_api_a_op_mode,
    .obj_size = sizeof(enum a_op_mode),
    .prototype_tag = caut_proto_enumeration,
    .prototype.c_enumeration = {
      .tag = caut_tag_8,
      .length = 2u,
    },
  },
  { /* a_debug_msg */
    .type_id = type_id_helium_atom_api_a_debug_msg,
    .obj_size = sizeof(struct a_debug_msg),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_u8,
      .max_length = 80u,
      .tag = caut_tag_8,
      .elem_span = ARR_ELEM_SPAN(uint8_t),
      .elem_offset = offsetof(struct a_debug_msg, elems),
    },
  },
  { /* a_data */
    .type_id = type_id_helium_atom_api_a_data,
    .obj_size = sizeof(struct a_data),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 1u,
      .fields = record_fields_helium_atom_api_a_data,
    },
  },
  { /* n_poll_data */
    .type_id = type_id_helium_atom_api_n_poll_data,
    .obj_size = sizeof(struct n_poll_data),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 4u,
      .fields = union_fields_helium_atom_api_n_poll_data,
    },
  },
  { /* n_cmd_poll_data_resp */
    .type_id = type_id_helium_atom_api_n_cmd_poll_data_resp,
    .obj_size = sizeof(struct n_cmd_poll_data_resp),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_n_cmd_poll_data_resp,
    },
  },
  { /* n_cmd_poll_data */
    .type_id = type_id_helium_atom_api_n_cmd_poll_data,
    .obj_size = sizeof(struct n_cmd_poll_data),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_n_cmd_poll_data,
    },
  },
  { /* a_cmd_security */
    .type_id = type_id_helium_atom_api_a_cmd_security,
    .obj_size = sizeof(struct a_cmd_security),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 8u,
      .fields = union_fields_helium_atom_api_a_cmd_security,
    },
  },
  { /* a_cmd_radio */
    .type_id = type_id_helium_atom_api_a_cmd_radio,
    .obj_size = sizeof(struct a_cmd_radio),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_a_cmd_radio,
    },
  },
  { /* a_cmd_pin */
    .type_id = type_id_helium_atom_api_a_cmd_pin,
    .obj_size = sizeof(struct a_cmd_pin),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 1u,
      .fields = record_fields_helium_atom_api_a_cmd_pin,
    },
  },
  { /* a_cmd_node */
    .type_id = type_id_helium_atom_api_a_cmd_node,
    .obj_size = sizeof(struct a_cmd_node),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 9u,
      .fields = union_fields_helium_atom_api_a_cmd_node,
    },
  },
  { /* a_cmd_config_set_time */
    .type_id = type_id_helium_atom_api_a_cmd_config_set_time,
    .obj_size = sizeof(struct a_cmd_config_set_time),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_a_cmd_config_set_time,
    },
  },
  { /* a_cmd_config_set_sleep_mode */
    .type_id = type_id_helium_atom_api_a_cmd_config_set_sleep_mode,
    .obj_size = sizeof(struct a_cmd_config_set_sleep_mode),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_a_cmd_config_set_sleep_mode,
    },
  },
  { /* a_cmd_config_set_op_mode */
    .type_id = type_id_helium_atom_api_a_cmd_config_set_op_mode,
    .obj_size = sizeof(struct a_cmd_config_set_op_mode),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_a_cmd_config_set_op_mode,
    },
  },
  { /* a_cmd_config_set_mfg_data */
    .type_id = type_id_helium_atom_api_a_cmd_config_set_mfg_data,
    .obj_size = sizeof(struct a_cmd_config_set_mfg_data),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_a_cmd_config_set_mfg_data,
    },
  },
  { /* a_cmd_config_set_mac */
    .type_id = type_id_helium_atom_api_a_cmd_config_set_mac,
    .obj_size = sizeof(struct a_cmd_config_set_mac),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_a_cmd_config_set_mac,
    },
  },
  { /* a_cmd_config_read_sleep_mode */
    .type_id = type_id_helium_atom_api_a_cmd_config_read_sleep_mode,
    .obj_size = sizeof(struct a_cmd_config_read_sleep_mode),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_a_cmd_config_read_sleep_mode,
    },
  },
  { /* a_cmd_config_read_mfg_data */
    .type_id = type_id_helium_atom_api_a_cmd_config_read_mfg_data,
    .obj_size = sizeof(struct a_cmd_config_read_mfg_data),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_a_cmd_config_read_mfg_data,
    },
  },
  { /* a_cmd_config_read_mac */
    .type_id = type_id_helium_atom_api_a_cmd_config_read_mac,
    .obj_size = sizeof(struct a_cmd_config_read_mac),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_a_cmd_config_read_mac,
    },
  },
  { /* a_cmd_config_get_atom_info */
    .type_id = type_id_helium_atom_api_a_cmd_config_get_atom_info,
    .obj_size = sizeof(struct a_cmd_config_get_atom_info),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_a_cmd_config_get_atom_info,
    },
  },
  { /* a_cmd_brd_reset */
    .type_id = type_id_helium_atom_api_a_cmd_brd_reset,
    .obj_size = sizeof(struct a_cmd_brd_reset),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_a_cmd_brd_reset,
    },
  },
  { /* a_cmd_brd_pin_out */
    .type_id = type_id_helium_atom_api_a_cmd_brd_pin_out,
    .obj_size = sizeof(struct a_cmd_brd_pin_out),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_a_cmd_brd_pin_out,
    },
  },
  { /* a_cmd_brd_pin_in */
    .type_id = type_id_helium_atom_api_a_cmd_brd_pin_in,
    .obj_size = sizeof(struct a_cmd_brd_pin_in),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_a_cmd_brd_pin_in,
    },
  },
  { /* a_cmd_board */
    .type_id = type_id_helium_atom_api_a_cmd_board,
    .obj_size = sizeof(struct a_cmd_board),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 4u,
      .fields = union_fields_helium_atom_api_a_cmd_board,
    },
  },
  { /* a_channel_report */
    .type_id = type_id_helium_atom_api_a_channel_report,
    .obj_size = sizeof(struct a_channel_report),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_a_channel_report,
    },
  },
  { /* a_channel_reports */
    .type_id = type_id_helium_atom_api_a_channel_reports,
    .obj_size = sizeof(struct a_channel_reports),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_a_channel_report,
      .max_length = 16u,
      .tag = caut_tag_8,
      .elem_span = ARR_ELEM_SPAN(struct a_channel_report),
      .elem_offset = offsetof(struct a_channel_reports, elems),
    },
  },
  { /* a_beacon_report */
    .type_id = type_id_helium_atom_api_a_beacon_report,
    .obj_size = sizeof(struct a_beacon_report),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 6u,
      .fields = record_fields_helium_atom_api_a_beacon_report,
    },
  },
  { /* a_beacon_reports */
    .type_id = type_id_helium_atom_api_a_beacon_reports,
    .obj_size = sizeof(struct a_beacon_reports),
    .prototype_tag = caut_proto_vector,
    .prototype.c_vector = {
      .ref_id = type_id_helium_atom_api_a_beacon_report,
      .max_length = 8u,
      .tag = caut_tag_8,
      .elem_span = ARR_ELEM_SPAN(struct a_beacon_report),
      .elem_offset = offsetof(struct a_beacon_reports, elems),
    },
  },
  { /* a_scan_report */
    .type_id = type_id_helium_atom_api_a_scan_report,
    .obj_size = sizeof(struct a_scan_report),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 3u,
      .fields = record_fields_helium_atom_api_a_scan_report,
    },
  },
  { /* a_baud_rate */
    .type_id = type_id_helium_atom_api_a_baud_rate,
    .obj_size = sizeof(enum a_baud_rate),
    .prototype_tag = caut_proto_enumeration,
    .prototype.c_enumeration = {
      .tag = caut_tag_8,
      .length = 5u,
    },
  },
  { /* a_cmd_config_read_baud_rate */
    .type_id = type_id_helium_atom_api_a_cmd_config_read_baud_rate,
    .obj_size = sizeof(struct a_cmd_config_read_baud_rate),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_a_cmd_config_read_baud_rate,
    },
  },
  { /* a_cmd_config_set_baud_rate */
    .type_id = type_id_helium_atom_api_a_cmd_config_set_baud_rate,
    .obj_size = sizeof(struct a_cmd_config_set_baud_rate),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 2u,
      .fields = union_fields_helium_atom_api_a_cmd_config_set_baud_rate,
    },
  },
  { /* a_cmd_config */
    .type_id = type_id_helium_atom_api_a_cmd_config,
    .obj_size = sizeof(struct a_cmd_config),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 11u,
      .fields = union_fields_helium_atom_api_a_cmd_config,
    },
  },
  { /* a_cmd */
    .type_id = type_id_helium_atom_api_a_cmd,
    .obj_size = sizeof(struct a_cmd),
    .prototype_tag = caut_proto_union,
    .prototype.c_union = {
      .tag = caut_tag_8,
      .field_count = 8u,
      .fields = union_fields_helium_atom_api_a_cmd,
    },
  },
  { /* a_cmd_t */
    .type_id = type_id_helium_atom_api_a_cmd_t,
    .obj_size = sizeof(struct a_cmd_t),
    .prototype_tag = caut_proto_record,
    .prototype.c_record = {
      .field_count = 2u,
      .fields = record_fields_helium_atom_api_a_cmd_t,
    },
  },
};

struct schema_descriptor const schema_descriptor_helium_atom_api = {
  .type_count = TYPE_COUNT_helium_atom_api,
  .types = type_descriptors_helium_atom_api,
};
