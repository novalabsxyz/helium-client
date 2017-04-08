#include "helium_atom_api_info.h"
#include "helium_atom_api_types.h"

#include "cauterize_info.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define ARR_ELEM_SPAN(TYPE) \
  (uintptr_t)&(((TYPE *)NULL)[1])

struct caut_field_info const enumeration_field_infos_helium_atom_api_s_sec_type[] = {
  { .name = "s_sha_204", .field_index = 0 },
  { .name = "s_ecc", .field_index = 1 },
};

struct caut_field_info const enumeration_field_infos_helium_atom_api_s_lstat[] = {
  { .name = "s_lstat_unlocked", .field_index = 0 },
  { .name = "s_lstat_cfg_locked", .field_index = 1 },
  { .name = "s_lstat_data_locked", .field_index = 2 },
  { .name = "s_lstat_cfg_data_locked", .field_index = 3 },
};

struct caut_field_info const record_field_infos_helium_atom_api_s_key_sig_req_rec[] = {
  { .name = "key_slot", .field_index = 0  },
  { .name = "key_req", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_s_gen_session_key_req[] = {
  { .name = "nonce", .field_index = 0  },
  { .name = "slot", .field_index = 1  },
};

struct caut_field_info const enumeration_field_infos_helium_atom_api_power_cmd[] = {
  { .name = "power_on", .field_index = 0 },
  { .name = "power_off", .field_index = 1 },
};

struct caut_field_info const enumeration_field_infos_helium_atom_api_pan_cmd[] = {
  { .name = "stop_pan", .field_index = 0 },
  { .name = "start_pan", .field_index = 1 },
};

struct caut_field_info const enumeration_field_infos_helium_atom_api_n_send_tx_status[] = {
  { .name = "ack", .field_index = 0 },
  { .name = "channel_access_failure", .field_index = 1 },
  { .name = "nack", .field_index = 2 },
};

struct caut_field_info const record_field_infos_helium_atom_api_n_send_req[] = {
  { .name = "payload", .field_index = 0  },
};

struct caut_field_info const record_field_infos_helium_atom_api_n_send_metadata[] = {
  { .name = "tx_status", .field_index = 0  },
};

struct caut_field_info const enumeration_field_infos_helium_atom_api_n_send_err[] = {
  { .name = "not_connected", .field_index = 0 },
  { .name = "radio_cant_send", .field_index = 1 },
  { .name = "dropped", .field_index = 2 },
  { .name = "payload_len", .field_index = 3 },
  { .name = "not_autonomous", .field_index = 4 },
};

struct caut_field_info const union_field_infos_helium_atom_api_n_send_resp[] = {
  { .name = "err", .field_index = 0  },
  { .name = "ok", .field_index = 1  },
};

struct caut_field_info const enumeration_field_infos_helium_atom_api_n_mode[] = {
  { .name = "api", .field_index = 0 },
  { .name = "autonomous", .field_index = 1 },
};

struct caut_field_info const record_field_infos_helium_atom_api_n_reflash_header[] = {
  { .name = "size", .field_index = 0  },
  { .name = "sha", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_n_reflash_data[] = {
  { .name = "transfer_id", .field_index = 0  },
  { .name = "offset", .field_index = 1  },
  { .name = "data", .field_index = 2  },
};

struct caut_field_info const union_field_infos_helium_atom_api_n_cmd_send[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const enumeration_field_infos_helium_atom_api_n_cmd_reflash_header_resp[] = {
  { .name = "ok", .field_index = 0 },
  { .name = "ok_duplicate", .field_index = 1 },
  { .name = "err_size", .field_index = 2 },
};

struct caut_field_info const union_field_infos_helium_atom_api_n_cmd_reflash_header[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_n_cmd_reflash_data_resp[] = {
  { .name = "ok_finished", .field_index = 0 },
  { .name = "ok_not_finished", .field_index = 1 },
  { .name = "err_no_transfer", .field_index = 2 },
  { .name = "err_out_of_order", .field_index = 3  },
  { .name = "err_transfer_id_mismatch", .field_index = 4  },
  { .name = "err_sha_mismatch", .field_index = 5  },
};

struct caut_field_info const union_field_infos_helium_atom_api_n_cmd_reflash_data[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_n_cmd_get_mode[] = {
  { .name = "req", .field_index = 0 },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_n_cmd_connection_status_resp[] = {
  { .name = "connected", .field_index = 0  },
};

struct caut_field_info const union_field_infos_helium_atom_api_n_cmd_connection_status[] = {
  { .name = "req", .field_index = 0 },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const enumeration_field_infos_helium_atom_api_n_cmd_connect_resp[] = {
  { .name = "ok", .field_index = 0 },
  { .name = "err_not_autonomous", .field_index = 1 },
  { .name = "err_fallback_to_slow_connect", .field_index = 2 },
};

struct caut_field_info const record_field_infos_helium_atom_api_s_get_derived_key_req[] = {
  { .name = "key_slot", .field_index = 0  },
  { .name = "long_add", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_s_key_update_req[] = {
  { .name = "key_slot", .field_index = 0  },
  { .name = "random", .field_index = 1  },
  { .name = "mac", .field_index = 2  },
};

struct caut_field_info const enumeration_field_infos_helium_atom_api_beacon_cmd[] = {
  { .name = "stop_beacon", .field_index = 0 },
  { .name = "start_beacon", .field_index = 1 },
};

struct caut_field_info const record_field_infos_helium_atom_api_a_version[] = {
  { .name = "product", .field_index = 0  },
  { .name = "major", .field_index = 1  },
  { .name = "minor", .field_index = 2  },
  { .name = "patch", .field_index = 3  },
};

struct caut_field_info const record_field_infos_helium_atom_api_n_connection[] = {
  { .name = "long_addr", .field_index = 0  },
  { .name = "pan_id", .field_index = 1  },
  { .name = "short_addr", .field_index = 2  },
  { .name = "gateway_addr", .field_index = 3  },
  { .name = "pan_seq", .field_index = 4  },
  { .name = "radio_index", .field_index = 5  },
  { .name = "connected", .field_index = 6  },
  { .name = "channel", .field_index = 7  },
  { .name = "speed", .field_index = 8  },
  { .name = "key_slot", .field_index = 9  },
  { .name = "sess_key", .field_index = 10  },
  { .name = "fw_version", .field_index = 11  },
};

struct caut_field_info const union_field_infos_helium_atom_api_n_cmd_sleep_resp[] = {
  { .name = "not_connected", .field_index = 0 },
  { .name = "not_autonomous", .field_index = 1 },
  { .name = "keep_awake", .field_index = 2 },
  { .name = "connection", .field_index = 3  },
  { .name = "needs_reset", .field_index = 4 },
};

struct caut_field_info const union_field_infos_helium_atom_api_n_cmd_sleep[] = {
  { .name = "req", .field_index = 0 },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_n_connection_quick[] = {
  { .name = "time", .field_index = 0  },
  { .name = "connection", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_n_cmd_connect_req[] = {
  { .name = "cold", .field_index = 0 },
  { .name = "quick", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_n_cmd_connect[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_a_time[] = {
  { .name = "sec", .field_index = 0  },
  { .name = "msec", .field_index = 1  },
};

struct caut_field_info const enumeration_field_infos_helium_atom_api_a_status[] = {
  { .name = "success", .field_index = 0 },
  { .name = "error", .field_index = 1 },
};

struct caut_field_info const record_field_infos_helium_atom_api_r_cmd_get_info_resp[] = {
  { .name = "status", .field_index = 0  },
  { .name = "part_num", .field_index = 1  },
  { .name = "min_channel", .field_index = 2  },
  { .name = "max_channel", .field_index = 3  },
  { .name = "pan_id", .field_index = 4  },
  { .name = "short_addr", .field_index = 5  },
  { .name = "channel", .field_index = 6  },
  { .name = "beaconing", .field_index = 7  },
};

struct caut_field_info const record_field_infos_helium_atom_api_s_gen_session_key_resp[] = {
  { .name = "status", .field_index = 0  },
  { .name = "session_key", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_s_cmd_gen_session_key[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_s_get_derived_key_resp[] = {
  { .name = "ssk", .field_index = 0  },
  { .name = "status", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_s_cmd_get_derived_key[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_s_key_sig_resp[] = {
  { .name = "status", .field_index = 0  },
  { .name = "sigs", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_s_cmd_key_sigs[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_s_resp_key_create[] = {
  { .name = "status", .field_index = 0  },
  { .name = "key", .field_index = 1  },
  { .name = "key_crc", .field_index = 2  },
};

struct caut_field_info const union_field_infos_helium_atom_api_s_cmd_key_create[] = {
  { .name = "req_key_slot", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_s_resp_lstat[] = {
  { .name = "status", .field_index = 0  },
  { .name = "lstat", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_s_cmd_read_lstat[] = {
  { .name = "req", .field_index = 0 },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_s_resp_part[] = {
  { .name = "status", .field_index = 0  },
  { .name = "sec_part_num", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_s_cmd_read_part[] = {
  { .name = "req", .field_index = 0 },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const enumeration_field_infos_helium_atom_api_a_sleep_mode[] = {
  { .name = "no_sleep", .field_index = 0 },
  { .name = "sleep_with_config", .field_index = 1 },
};

struct caut_field_info const record_field_infos_helium_atom_api_a_resp_u8[] = {
  { .name = "status", .field_index = 0  },
  { .name = "value", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_a_resp_u64[] = {
  { .name = "status", .field_index = 0  },
  { .name = "value", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_a_resp_sleep_mode[] = {
  { .name = "status", .field_index = 0  },
  { .name = "sleep_mode", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_a_resp_mfg_data[] = {
  { .name = "status", .field_index = 0  },
  { .name = "value", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_a_resp_get_atom_info[] = {
  { .name = "status", .field_index = 0  },
  { .name = "radio_count", .field_index = 1  },
  { .name = "uptime", .field_index = 2  },
  { .name = "time", .field_index = 3  },
  { .name = "fw_version", .field_index = 4  },
  { .name = "schema_fp", .field_index = 5  },
};

struct caut_field_info const record_field_infos_helium_atom_api_a_resp_gen[] = {
  { .name = "status", .field_index = 0  },
};

struct caut_field_info const union_field_infos_helium_atom_api_n_cmd_set_mode[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_r_cmd_beacon[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_r_cmd_pan[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_r_cmd_pan_fr[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_r_cmd_power[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_r_cmd_scan_start[] = {
  { .name = "req", .field_index = 0 },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_r_cmd_set_chan[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_r_cmd_set_pan_id[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_r_cmd_set_sh_addr[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_s_cmd_init[] = {
  { .name = "req", .field_index = 0 },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_s_cmd_key_update[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_s_cmd_lock[] = {
  { .name = "req", .field_index = 0 },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const enumeration_field_infos_helium_atom_api_a_radio_type[] = {
  { .name = "r_sub_g", .field_index = 0 },
  { .name = "r_24_g", .field_index = 1 },
};

struct caut_field_info const union_field_infos_helium_atom_api_r_cmd_get_info[] = {
  { .name = "req_rtype", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_r_cmd[] = {
  { .name = "scan_start", .field_index = 0  },
  { .name = "set_pan_id", .field_index = 1  },
  { .name = "set_sh_addr", .field_index = 2  },
  { .name = "set_channel", .field_index = 3  },
  { .name = "pan", .field_index = 4  },
  { .name = "beacon", .field_index = 5  },
  { .name = "pan_fr", .field_index = 6  },
  { .name = "power", .field_index = 7  },
  { .name = "get_info", .field_index = 8  },
};

struct caut_field_info const enumeration_field_infos_helium_atom_api_a_op_mode[] = {
  { .name = "default", .field_index = 0 },
  { .name = "maintenence", .field_index = 1 },
};

struct caut_field_info const record_field_infos_helium_atom_api_a_data[] = {
  { .name = "buf", .field_index = 0  },
};

struct caut_field_info const union_field_infos_helium_atom_api_n_poll_data[] = {
  { .name = "none", .field_index = 0 },
  { .name = "frame", .field_index = 1  },
  { .name = "err_not_autonomous", .field_index = 2 },
  { .name = "need_reset", .field_index = 3 },
};

struct caut_field_info const record_field_infos_helium_atom_api_n_cmd_poll_data_resp[] = {
  { .name = "frames_droped", .field_index = 0  },
  { .name = "poll_data", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_n_cmd_poll_data[] = {
  { .name = "req", .field_index = 0 },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_security[] = {
  { .name = "read_part", .field_index = 0  },
  { .name = "init", .field_index = 1  },
  { .name = "read_lstat", .field_index = 2  },
  { .name = "key_create", .field_index = 3  },
  { .name = "key_update", .field_index = 4  },
  { .name = "lock", .field_index = 5  },
  { .name = "get_key_sigs", .field_index = 6  },
  { .name = "gen_session_key", .field_index = 7  },
};

struct caut_field_info const record_field_infos_helium_atom_api_a_cmd_radio[] = {
  { .name = "radio_id", .field_index = 0  },
  { .name = "cmd", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_a_cmd_pin[] = {
  { .name = "pin_num", .field_index = 0  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_node[] = {
  { .name = "set_mode", .field_index = 0  },
  { .name = "get_mode", .field_index = 1  },
  { .name = "reflash_header", .field_index = 2  },
  { .name = "reflash_data", .field_index = 3  },
  { .name = "send", .field_index = 4  },
  { .name = "connection_status", .field_index = 5  },
  { .name = "poll_data", .field_index = 6  },
  { .name = "connect", .field_index = 7  },
  { .name = "sleep", .field_index = 8  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_config_set_time[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_config_set_sleep_mode[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_config_set_op_mode[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_config_set_mfg_data[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_config_set_mac[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_config_read_sleep_mode[] = {
  { .name = "req", .field_index = 0 },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_config_read_mfg_data[] = {
  { .name = "req", .field_index = 0 },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_config_read_mac[] = {
  { .name = "req", .field_index = 0 },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_config_get_atom_info[] = {
  { .name = "req", .field_index = 0 },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_brd_reset[] = {
  { .name = "req", .field_index = 0 },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_brd_pin_out[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_brd_pin_in[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_board[] = {
  { .name = "reset", .field_index = 0  },
  { .name = "pin_set", .field_index = 1  },
  { .name = "pin_clear", .field_index = 2  },
  { .name = "pin_read", .field_index = 3  },
};

struct caut_field_info const record_field_infos_helium_atom_api_a_channel_report[] = {
  { .name = "channel", .field_index = 0  },
  { .name = "energy", .field_index = 1  },
};

struct caut_field_info const record_field_infos_helium_atom_api_a_beacon_report[] = {
  { .name = "pan_id", .field_index = 0  },
  { .name = "short_addr", .field_index = 1  },
  { .name = "lqi", .field_index = 2  },
  { .name = "ed", .field_index = 3  },
  { .name = "channel", .field_index = 4  },
  { .name = "time", .field_index = 5  },
};

struct caut_field_info const record_field_infos_helium_atom_api_a_scan_report[] = {
  { .name = "radio_index", .field_index = 0  },
  { .name = "channels", .field_index = 1  },
  { .name = "beacons", .field_index = 2  },
};

struct caut_field_info const enumeration_field_infos_helium_atom_api_a_baud_rate[] = {
  { .name = "br_9600", .field_index = 0 },
  { .name = "br_19200", .field_index = 1 },
  { .name = "br_38400", .field_index = 2 },
  { .name = "br_115200", .field_index = 3 },
  { .name = "br_256400", .field_index = 4 },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_config_read_baud_rate[] = {
  { .name = "req", .field_index = 0 },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_config_set_baud_rate[] = {
  { .name = "req", .field_index = 0  },
  { .name = "resp", .field_index = 1  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd_config[] = {
  { .name = "set_op_mode", .field_index = 0  },
  { .name = "set_mac", .field_index = 1  },
  { .name = "read_mac", .field_index = 2  },
  { .name = "set_mfg_data", .field_index = 3  },
  { .name = "read_mfg_data", .field_index = 4  },
  { .name = "set_sleep_mode", .field_index = 5  },
  { .name = "read_sleep_mode", .field_index = 6  },
  { .name = "set_baud_rate", .field_index = 7  },
  { .name = "read_baud_rate", .field_index = 8  },
  { .name = "set_time", .field_index = 9  },
  { .name = "get_atom_info", .field_index = 10  },
};

struct caut_field_info const union_field_infos_helium_atom_api_a_cmd[] = {
  { .name = "board_cmd", .field_index = 0  },
  { .name = "config_cmd", .field_index = 1  },
  { .name = "security_cmd", .field_index = 2  },
  { .name = "radio_cmd", .field_index = 3  },
  { .name = "data", .field_index = 4  },
  { .name = "scan_report", .field_index = 5  },
  { .name = "debug", .field_index = 6  },
  { .name = "node_cmd", .field_index = 7  },
};

struct caut_field_info const record_field_infos_helium_atom_api_a_cmd_t[] = {
  { .name = "sequence", .field_index = 0  },
  { .name = "cmd", .field_index = 1  },
};


struct type_info const type_info_helium_atom_api[TYPE_COUNT_helium_atom_api] = {
  {
    .name = "s_ssk",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_ssk,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_ssk,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_s_ssk,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector s_ssk. */
  },
  {
    .name = "s_sig",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_sig,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_sig,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_s_sig,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector s_sig. */
  },
  {
    .name = "s_sigs",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_sigs,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_sigs,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_s_sigs,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector s_sigs. */
  },
  {
    .name = "s_sec_type",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_sec_type,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_sec_type,
    .depth = 1,
    .fingerprint = TYPE_FP_helium_atom_api_s_sec_type,
    .prototype_tag = caut_proto_enumeration,
    .prototype.i_enumeration = {
      .field_count = 2u,
      .fields = enumeration_field_infos_helium_atom_api_s_sec_type,
    },
  },
  {
    .name = "s_part_num",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_part_num,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_part_num,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_s_part_num,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector s_part_num. */
  },
  {
    .name = "s_lstat",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_lstat,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_lstat,
    .depth = 1,
    .fingerprint = TYPE_FP_helium_atom_api_s_lstat,
    .prototype_tag = caut_proto_enumeration,
    .prototype.i_enumeration = {
      .field_count = 4u,
      .fields = enumeration_field_infos_helium_atom_api_s_lstat,
    },
  },
  {
    .name = "s_key_sigs",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_key_sigs,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_key_sigs,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_s_key_sigs,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector s_key_sigs. */
  },
  {
    .name = "s_key_sig_req",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_key_sig_req,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_key_sig_req,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_s_key_sig_req,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector s_key_sig_req. */
  },
  {
    .name = "s_key_sig_req_rec",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_key_sig_req_rec,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_key_sig_req_rec,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_s_key_sig_req_rec,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_s_key_sig_req_rec,
    },
  },
  {
    .name = "s_gen_session_key_req",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_gen_session_key_req,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_gen_session_key_req,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_s_gen_session_key_req,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_s_gen_session_key_req,
    },
  },
  {
    .name = "power_cmd",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_power_cmd,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_power_cmd,
    .depth = 1,
    .fingerprint = TYPE_FP_helium_atom_api_power_cmd,
    .prototype_tag = caut_proto_enumeration,
    .prototype.i_enumeration = {
      .field_count = 2u,
      .fields = enumeration_field_infos_helium_atom_api_power_cmd,
    },
  },
  {
    .name = "pan_frame",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_pan_frame,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_pan_frame,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_pan_frame,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector pan_frame. */
  },
  {
    .name = "pan_cmd",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_pan_cmd,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_pan_cmd,
    .depth = 1,
    .fingerprint = TYPE_FP_helium_atom_api_pan_cmd,
    .prototype_tag = caut_proto_enumeration,
    .prototype.i_enumeration = {
      .field_count = 2u,
      .fields = enumeration_field_infos_helium_atom_api_pan_cmd,
    },
  },
  {
    .name = "n_send_tx_status",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_send_tx_status,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_send_tx_status,
    .depth = 1,
    .fingerprint = TYPE_FP_helium_atom_api_n_send_tx_status,
    .prototype_tag = caut_proto_enumeration,
    .prototype.i_enumeration = {
      .field_count = 3u,
      .fields = enumeration_field_infos_helium_atom_api_n_send_tx_status,
    },
  },
  {
    .name = "n_send_req",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_send_req,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_send_req,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_n_send_req,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 1u,
      .fields = record_field_infos_helium_atom_api_n_send_req,
    },
  },
  {
    .name = "n_send_metadata",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_send_metadata,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_send_metadata,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_n_send_metadata,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 1u,
      .fields = record_field_infos_helium_atom_api_n_send_metadata,
    },
  },
  {
    .name = "n_send_err",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_send_err,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_send_err,
    .depth = 1,
    .fingerprint = TYPE_FP_helium_atom_api_n_send_err,
    .prototype_tag = caut_proto_enumeration,
    .prototype.i_enumeration = {
      .field_count = 5u,
      .fields = enumeration_field_infos_helium_atom_api_n_send_err,
    },
  },
  {
    .name = "n_send_resp",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_send_resp,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_send_resp,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_n_send_resp,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_n_send_resp,
    },
  },
  {
    .name = "n_mode",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_mode,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_mode,
    .depth = 1,
    .fingerprint = TYPE_FP_helium_atom_api_n_mode,
    .prototype_tag = caut_proto_enumeration,
    .prototype.i_enumeration = {
      .field_count = 2u,
      .fields = enumeration_field_infos_helium_atom_api_n_mode,
    },
  },
  {
    .name = "n_img_sha",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_img_sha,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_img_sha,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_n_img_sha,
    .prototype_tag = caut_proto_array,
    /* No extra information for array n_img_sha. */
  },
  {
    .name = "n_reflash_header",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_reflash_header,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_reflash_header,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_n_reflash_header,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_n_reflash_header,
    },
  },
  {
    .name = "n_img_id",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_img_id,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_img_id,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_n_img_id,
    .prototype_tag = caut_proto_array,
    /* No extra information for array n_img_id. */
  },
  {
    .name = "n_img_data",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_img_data,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_img_data,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_n_img_data,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector n_img_data. */
  },
  {
    .name = "n_reflash_data",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_reflash_data,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_reflash_data,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_n_reflash_data,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 3u,
      .fields = record_field_infos_helium_atom_api_n_reflash_data,
    },
  },
  {
    .name = "n_cmd_send",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_send,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_send,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_send,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_n_cmd_send,
    },
  },
  {
    .name = "n_cmd_reflash_header_resp",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_reflash_header_resp,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_reflash_header_resp,
    .depth = 1,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_reflash_header_resp,
    .prototype_tag = caut_proto_enumeration,
    .prototype.i_enumeration = {
      .field_count = 3u,
      .fields = enumeration_field_infos_helium_atom_api_n_cmd_reflash_header_resp,
    },
  },
  {
    .name = "n_cmd_reflash_header",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_reflash_header,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_reflash_header,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_reflash_header,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_n_cmd_reflash_header,
    },
  },
  {
    .name = "n_cmd_reflash_data_resp",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_reflash_data_resp,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_reflash_data_resp,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_reflash_data_resp,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 6u,
      .fields = union_field_infos_helium_atom_api_n_cmd_reflash_data_resp,
    },
  },
  {
    .name = "n_cmd_reflash_data",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_reflash_data,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_reflash_data,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_reflash_data,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_n_cmd_reflash_data,
    },
  },
  {
    .name = "n_cmd_get_mode",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_get_mode,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_get_mode,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_get_mode,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_n_cmd_get_mode,
    },
  },
  {
    .name = "n_cmd_connection_status_resp",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_connection_status_resp,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_connection_status_resp,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_connection_status_resp,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 1u,
      .fields = record_field_infos_helium_atom_api_n_cmd_connection_status_resp,
    },
  },
  {
    .name = "n_cmd_connection_status",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_connection_status,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_connection_status,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_connection_status,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_n_cmd_connection_status,
    },
  },
  {
    .name = "n_cmd_connect_resp",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_connect_resp,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_connect_resp,
    .depth = 1,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_connect_resp,
    .prototype_tag = caut_proto_enumeration,
    .prototype.i_enumeration = {
      .field_count = 3u,
      .fields = enumeration_field_infos_helium_atom_api_n_cmd_connect_resp,
    },
  },
  {
    .name = "h_scan",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_h_scan,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_h_scan,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_h_scan,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector h_scan. */
  },
  {
    .name = "h_mfg_data",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_h_mfg_data,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_h_mfg_data,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_h_mfg_data,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector h_mfg_data. */
  },
  {
    .name = "h_mac",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_h_mac,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_h_mac,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_h_mac,
    .prototype_tag = caut_proto_synonym,
    /* No extra information for synonym h_mac. */
  },
  {
    .name = "s_get_derived_key_req",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_get_derived_key_req,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_get_derived_key_req,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_s_get_derived_key_req,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_s_get_derived_key_req,
    },
  },
  {
    .name = "h_data_u8",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_h_data_u8,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_h_data_u8,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_h_data_u8,
    .prototype_tag = caut_proto_synonym,
    /* No extra information for synonym h_data_u8. */
  },
  {
    .name = "h_data_u32",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_h_data_u32,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_h_data_u32,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_h_data_u32,
    .prototype_tag = caut_proto_synonym,
    /* No extra information for synonym h_data_u32. */
  },
  {
    .name = "h_data_u16",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_h_data_u16,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_h_data_u16,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_h_data_u16,
    .prototype_tag = caut_proto_synonym,
    /* No extra information for synonym h_data_u16. */
  },
  {
    .name = "h_buf_32b",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_h_buf_32b,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_h_buf_32b,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_h_buf_32b,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector h_buf_32b. */
  },
  {
    .name = "s_key_update_req",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_key_update_req,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_key_update_req,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_s_key_update_req,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 3u,
      .fields = record_field_infos_helium_atom_api_s_key_update_req,
    },
  },
  {
    .name = "h_buf_20b",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_h_buf_20b,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_h_buf_20b,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_h_buf_20b,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector h_buf_20b. */
  },
  {
    .name = "h_buf",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_h_buf,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_h_buf,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_h_buf,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector h_buf. */
  },
  {
    .name = "h_arr_32b",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_h_arr_32b,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_h_arr_32b,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_h_arr_32b,
    .prototype_tag = caut_proto_array,
    /* No extra information for array h_arr_32b. */
  },
  {
    .name = "beacon_cmd",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_beacon_cmd,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_beacon_cmd,
    .depth = 1,
    .fingerprint = TYPE_FP_helium_atom_api_beacon_cmd,
    .prototype_tag = caut_proto_enumeration,
    .prototype.i_enumeration = {
      .field_count = 2u,
      .fields = enumeration_field_infos_helium_atom_api_beacon_cmd,
    },
  },
  {
    .name = "a_version",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_version,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_version,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_a_version,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 4u,
      .fields = record_field_infos_helium_atom_api_a_version,
    },
  },
  {
    .name = "n_connection",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_connection,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_connection,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_n_connection,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 12u,
      .fields = record_field_infos_helium_atom_api_n_connection,
    },
  },
  {
    .name = "n_cmd_sleep_resp",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_sleep_resp,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_sleep_resp,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_sleep_resp,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 5u,
      .fields = union_field_infos_helium_atom_api_n_cmd_sleep_resp,
    },
  },
  {
    .name = "n_cmd_sleep",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_sleep,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_sleep,
    .depth = 5,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_sleep,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_n_cmd_sleep,
    },
  },
  {
    .name = "n_connection_quick",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_connection_quick,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_connection_quick,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_n_connection_quick,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_n_connection_quick,
    },
  },
  {
    .name = "n_cmd_connect_req",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_connect_req,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_connect_req,
    .depth = 5,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_connect_req,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_n_cmd_connect_req,
    },
  },
  {
    .name = "n_cmd_connect",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_connect,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_connect,
    .depth = 6,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_connect,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_n_cmd_connect,
    },
  },
  {
    .name = "a_time",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_time,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_time,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_a_time,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_a_time,
    },
  },
  {
    .name = "a_status",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_status,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_status,
    .depth = 1,
    .fingerprint = TYPE_FP_helium_atom_api_a_status,
    .prototype_tag = caut_proto_enumeration,
    .prototype.i_enumeration = {
      .field_count = 2u,
      .fields = enumeration_field_infos_helium_atom_api_a_status,
    },
  },
  {
    .name = "r_cmd_get_info_resp",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_r_cmd_get_info_resp,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_r_cmd_get_info_resp,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_r_cmd_get_info_resp,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 8u,
      .fields = record_field_infos_helium_atom_api_r_cmd_get_info_resp,
    },
  },
  {
    .name = "s_gen_session_key_resp",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_gen_session_key_resp,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_gen_session_key_resp,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_s_gen_session_key_resp,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_s_gen_session_key_resp,
    },
  },
  {
    .name = "s_cmd_gen_session_key",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_cmd_gen_session_key,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_cmd_gen_session_key,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_s_cmd_gen_session_key,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_s_cmd_gen_session_key,
    },
  },
  {
    .name = "s_get_derived_key_resp",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_get_derived_key_resp,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_get_derived_key_resp,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_s_get_derived_key_resp,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_s_get_derived_key_resp,
    },
  },
  {
    .name = "s_cmd_get_derived_key",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_cmd_get_derived_key,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_cmd_get_derived_key,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_s_cmd_get_derived_key,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_s_cmd_get_derived_key,
    },
  },
  {
    .name = "s_key_sig_resp",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_key_sig_resp,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_key_sig_resp,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_s_key_sig_resp,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_s_key_sig_resp,
    },
  },
  {
    .name = "s_cmd_key_sigs",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_cmd_key_sigs,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_cmd_key_sigs,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_s_cmd_key_sigs,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_s_cmd_key_sigs,
    },
  },
  {
    .name = "s_resp_key_create",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_resp_key_create,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_resp_key_create,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_s_resp_key_create,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 3u,
      .fields = record_field_infos_helium_atom_api_s_resp_key_create,
    },
  },
  {
    .name = "s_cmd_key_create",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_cmd_key_create,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_cmd_key_create,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_s_cmd_key_create,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_s_cmd_key_create,
    },
  },
  {
    .name = "s_resp_lstat",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_resp_lstat,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_resp_lstat,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_s_resp_lstat,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_s_resp_lstat,
    },
  },
  {
    .name = "s_cmd_read_lstat",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_cmd_read_lstat,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_cmd_read_lstat,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_s_cmd_read_lstat,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_s_cmd_read_lstat,
    },
  },
  {
    .name = "s_resp_part",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_resp_part,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_resp_part,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_s_resp_part,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_s_resp_part,
    },
  },
  {
    .name = "s_cmd_read_part",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_cmd_read_part,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_cmd_read_part,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_s_cmd_read_part,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_s_cmd_read_part,
    },
  },
  {
    .name = "a_sleep_mode",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_sleep_mode,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_sleep_mode,
    .depth = 1,
    .fingerprint = TYPE_FP_helium_atom_api_a_sleep_mode,
    .prototype_tag = caut_proto_enumeration,
    .prototype.i_enumeration = {
      .field_count = 2u,
      .fields = enumeration_field_infos_helium_atom_api_a_sleep_mode,
    },
  },
  {
    .name = "a_resp_u8",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_resp_u8,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_resp_u8,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_a_resp_u8,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_a_resp_u8,
    },
  },
  {
    .name = "a_resp_u64",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_resp_u64,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_resp_u64,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_a_resp_u64,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_a_resp_u64,
    },
  },
  {
    .name = "a_resp_sleep_mode",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_resp_sleep_mode,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_resp_sleep_mode,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_a_resp_sleep_mode,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_a_resp_sleep_mode,
    },
  },
  {
    .name = "a_resp_mfg_data",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_resp_mfg_data,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_resp_mfg_data,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_resp_mfg_data,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_a_resp_mfg_data,
    },
  },
  {
    .name = "a_resp_get_atom_info",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_resp_get_atom_info,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_resp_get_atom_info,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_resp_get_atom_info,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 6u,
      .fields = record_field_infos_helium_atom_api_a_resp_get_atom_info,
    },
  },
  {
    .name = "a_resp_gen",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_resp_gen,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_resp_gen,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_a_resp_gen,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 1u,
      .fields = record_field_infos_helium_atom_api_a_resp_gen,
    },
  },
  {
    .name = "n_cmd_set_mode",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_set_mode,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_set_mode,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_set_mode,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_n_cmd_set_mode,
    },
  },
  {
    .name = "r_cmd_beacon",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_r_cmd_beacon,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_r_cmd_beacon,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_r_cmd_beacon,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_r_cmd_beacon,
    },
  },
  {
    .name = "r_cmd_pan",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_r_cmd_pan,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_r_cmd_pan,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_r_cmd_pan,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_r_cmd_pan,
    },
  },
  {
    .name = "r_cmd_pan_fr",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_r_cmd_pan_fr,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_r_cmd_pan_fr,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_r_cmd_pan_fr,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_r_cmd_pan_fr,
    },
  },
  {
    .name = "r_cmd_power",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_r_cmd_power,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_r_cmd_power,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_r_cmd_power,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_r_cmd_power,
    },
  },
  {
    .name = "r_cmd_scan_start",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_r_cmd_scan_start,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_r_cmd_scan_start,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_r_cmd_scan_start,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_r_cmd_scan_start,
    },
  },
  {
    .name = "r_cmd_set_chan",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_r_cmd_set_chan,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_r_cmd_set_chan,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_r_cmd_set_chan,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_r_cmd_set_chan,
    },
  },
  {
    .name = "r_cmd_set_pan_id",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_r_cmd_set_pan_id,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_r_cmd_set_pan_id,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_r_cmd_set_pan_id,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_r_cmd_set_pan_id,
    },
  },
  {
    .name = "r_cmd_set_sh_addr",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_r_cmd_set_sh_addr,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_r_cmd_set_sh_addr,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_r_cmd_set_sh_addr,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_r_cmd_set_sh_addr,
    },
  },
  {
    .name = "s_cmd_init",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_cmd_init,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_cmd_init,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_s_cmd_init,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_s_cmd_init,
    },
  },
  {
    .name = "s_cmd_key_update",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_cmd_key_update,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_cmd_key_update,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_s_cmd_key_update,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_s_cmd_key_update,
    },
  },
  {
    .name = "s_cmd_lock",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_s_cmd_lock,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_s_cmd_lock,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_s_cmd_lock,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_s_cmd_lock,
    },
  },
  {
    .name = "a_radio_type",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_radio_type,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_radio_type,
    .depth = 1,
    .fingerprint = TYPE_FP_helium_atom_api_a_radio_type,
    .prototype_tag = caut_proto_enumeration,
    .prototype.i_enumeration = {
      .field_count = 2u,
      .fields = enumeration_field_infos_helium_atom_api_a_radio_type,
    },
  },
  {
    .name = "r_cmd_get_info",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_r_cmd_get_info,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_r_cmd_get_info,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_r_cmd_get_info,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_r_cmd_get_info,
    },
  },
  {
    .name = "r_cmd",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_r_cmd,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_r_cmd,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_r_cmd,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 9u,
      .fields = union_field_infos_helium_atom_api_r_cmd,
    },
  },
  {
    .name = "a_op_mode",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_op_mode,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_op_mode,
    .depth = 1,
    .fingerprint = TYPE_FP_helium_atom_api_a_op_mode,
    .prototype_tag = caut_proto_enumeration,
    .prototype.i_enumeration = {
      .field_count = 2u,
      .fields = enumeration_field_infos_helium_atom_api_a_op_mode,
    },
  },
  {
    .name = "a_debug_msg",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_debug_msg,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_debug_msg,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_a_debug_msg,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector a_debug_msg. */
  },
  {
    .name = "a_data",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_data,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_data,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_data,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 1u,
      .fields = record_field_infos_helium_atom_api_a_data,
    },
  },
  {
    .name = "n_poll_data",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_poll_data,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_poll_data,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_n_poll_data,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 4u,
      .fields = union_field_infos_helium_atom_api_n_poll_data,
    },
  },
  {
    .name = "n_cmd_poll_data_resp",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_poll_data_resp,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_poll_data_resp,
    .depth = 5,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_poll_data_resp,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_n_cmd_poll_data_resp,
    },
  },
  {
    .name = "n_cmd_poll_data",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_n_cmd_poll_data,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_n_cmd_poll_data,
    .depth = 6,
    .fingerprint = TYPE_FP_helium_atom_api_n_cmd_poll_data,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_n_cmd_poll_data,
    },
  },
  {
    .name = "a_cmd_security",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_security,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_security,
    .depth = 5,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_security,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 8u,
      .fields = union_field_infos_helium_atom_api_a_cmd_security,
    },
  },
  {
    .name = "a_cmd_radio",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_radio,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_radio,
    .depth = 5,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_radio,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_a_cmd_radio,
    },
  },
  {
    .name = "a_cmd_pin",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_pin,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_pin,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_pin,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 1u,
      .fields = record_field_infos_helium_atom_api_a_cmd_pin,
    },
  },
  {
    .name = "a_cmd_node",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_node,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_node,
    .depth = 7,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_node,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 9u,
      .fields = union_field_infos_helium_atom_api_a_cmd_node,
    },
  },
  {
    .name = "a_cmd_config_set_time",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_config_set_time,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_config_set_time,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_config_set_time,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_a_cmd_config_set_time,
    },
  },
  {
    .name = "a_cmd_config_set_sleep_mode",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_config_set_sleep_mode,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_config_set_sleep_mode,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_config_set_sleep_mode,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_a_cmd_config_set_sleep_mode,
    },
  },
  {
    .name = "a_cmd_config_set_op_mode",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_config_set_op_mode,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_config_set_op_mode,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_config_set_op_mode,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_a_cmd_config_set_op_mode,
    },
  },
  {
    .name = "a_cmd_config_set_mfg_data",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_config_set_mfg_data,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_config_set_mfg_data,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_config_set_mfg_data,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_a_cmd_config_set_mfg_data,
    },
  },
  {
    .name = "a_cmd_config_set_mac",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_config_set_mac,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_config_set_mac,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_config_set_mac,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_a_cmd_config_set_mac,
    },
  },
  {
    .name = "a_cmd_config_read_sleep_mode",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_config_read_sleep_mode,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_config_read_sleep_mode,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_config_read_sleep_mode,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_a_cmd_config_read_sleep_mode,
    },
  },
  {
    .name = "a_cmd_config_read_mfg_data",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_config_read_mfg_data,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_config_read_mfg_data,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_config_read_mfg_data,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_a_cmd_config_read_mfg_data,
    },
  },
  {
    .name = "a_cmd_config_read_mac",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_config_read_mac,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_config_read_mac,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_config_read_mac,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_a_cmd_config_read_mac,
    },
  },
  {
    .name = "a_cmd_config_get_atom_info",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_config_get_atom_info,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_config_get_atom_info,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_config_get_atom_info,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_a_cmd_config_get_atom_info,
    },
  },
  {
    .name = "a_cmd_brd_reset",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_brd_reset,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_brd_reset,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_brd_reset,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_a_cmd_brd_reset,
    },
  },
  {
    .name = "a_cmd_brd_pin_out",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_brd_pin_out,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_brd_pin_out,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_brd_pin_out,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_a_cmd_brd_pin_out,
    },
  },
  {
    .name = "a_cmd_brd_pin_in",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_brd_pin_in,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_brd_pin_in,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_brd_pin_in,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_a_cmd_brd_pin_in,
    },
  },
  {
    .name = "a_cmd_board",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_board,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_board,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_board,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 4u,
      .fields = union_field_infos_helium_atom_api_a_cmd_board,
    },
  },
  {
    .name = "a_channel_report",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_channel_report,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_channel_report,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_a_channel_report,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_a_channel_report,
    },
  },
  {
    .name = "a_channel_reports",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_channel_reports,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_channel_reports,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_channel_reports,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector a_channel_reports. */
  },
  {
    .name = "a_beacon_report",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_beacon_report,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_beacon_report,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_a_beacon_report,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 6u,
      .fields = record_field_infos_helium_atom_api_a_beacon_report,
    },
  },
  {
    .name = "a_beacon_reports",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_beacon_reports,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_beacon_reports,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_beacon_reports,
    .prototype_tag = caut_proto_vector,
    /* No extra information for vector a_beacon_reports. */
  },
  {
    .name = "a_scan_report",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_scan_report,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_scan_report,
    .depth = 4,
    .fingerprint = TYPE_FP_helium_atom_api_a_scan_report,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 3u,
      .fields = record_field_infos_helium_atom_api_a_scan_report,
    },
  },
  {
    .name = "a_baud_rate",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_baud_rate,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_baud_rate,
    .depth = 1,
    .fingerprint = TYPE_FP_helium_atom_api_a_baud_rate,
    .prototype_tag = caut_proto_enumeration,
    .prototype.i_enumeration = {
      .field_count = 5u,
      .fields = enumeration_field_infos_helium_atom_api_a_baud_rate,
    },
  },
  {
    .name = "a_cmd_config_read_baud_rate",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_config_read_baud_rate,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_config_read_baud_rate,
    .depth = 2,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_config_read_baud_rate,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_a_cmd_config_read_baud_rate,
    },
  },
  {
    .name = "a_cmd_config_set_baud_rate",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_config_set_baud_rate,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_config_set_baud_rate,
    .depth = 3,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_config_set_baud_rate,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 2u,
      .fields = union_field_infos_helium_atom_api_a_cmd_config_set_baud_rate,
    },
  },
  {
    .name = "a_cmd_config",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_config,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_config,
    .depth = 5,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_config,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 11u,
      .fields = union_field_infos_helium_atom_api_a_cmd_config,
    },
  },
  {
    .name = "a_cmd",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd,
    .depth = 8,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd,
    .prototype_tag = caut_proto_union,
    .prototype.i_union = {
      .field_count = 8u,
      .fields = union_field_infos_helium_atom_api_a_cmd,
    },
  },
  {
    .name = "a_cmd_t",
    .min_size = TYPE_SIZE_MIN_helium_atom_api_a_cmd_t,
    .max_size = TYPE_SIZE_MAX_helium_atom_api_a_cmd_t,
    .depth = 9,
    .fingerprint = TYPE_FP_helium_atom_api_a_cmd_t,
    .prototype_tag = caut_proto_record,
    .prototype.i_record = {
      .field_count = 2u,
      .fields = record_field_infos_helium_atom_api_a_cmd_t,
    },
  },
};

struct schema_info const schema_info_helium_atom_api = {
  .name = "helium_atom_api",
  .fingerprint = SCHEMA_FP_helium_atom_api,
  .min_size = SCHEMA_SIZE_MIN_helium_atom_api,
  .max_size = SCHEMA_SIZE_MAX_helium_atom_api,
  .depth = 9,
  .type_count = TYPE_COUNT_helium_atom_api,
  .types = type_info_helium_atom_api,
};
