#ifndef AM_ATOM_API_EXTRACTORS_H
#define AM_ATOM_API_EXTRACTORS_H

#include "helium_atom_api.h"
#include <assert.h>
#include <stdint.h>

static inline enum a_status const * extract__node_cmd__set_mode(struct a_cmd_t const * obj) {
    if (obj &&
        (obj->cmd._tag == a_cmd_tag_node_cmd) &&
        (obj->cmd.node_cmd._tag == a_cmd_node_tag_set_mode) &&
        (obj->cmd.node_cmd.set_mode._tag == n_cmd_set_mode_tag_resp)) {
        return &obj->cmd.node_cmd.set_mode.resp.status;
    } else {
        return NULL;
    }
}

static inline struct a_resp_u64 const * extract__config_cmd__read_mac(struct a_cmd_t const * obj) {
    if (obj &&
        (obj->cmd._tag == a_cmd_tag_config_cmd) &&
        (obj->cmd.config_cmd._tag == a_cmd_config_tag_read_mac) &&
        (obj->cmd.config_cmd.read_mac._tag == a_cmd_config_read_mac_tag_resp)) {
        return &obj->cmd.config_cmd.read_mac.resp;
    } else {
        return NULL;
    }
}

static inline enum n_cmd_connect_resp const * extract__node_cmd__connect(struct a_cmd_t const * obj) {
    if (obj &&
        (obj->cmd._tag == a_cmd_tag_node_cmd) &&
        (obj->cmd.node_cmd._tag == a_cmd_node_tag_connect) &&
        (obj->cmd.node_cmd.connect._tag == n_cmd_connect_tag_resp)) {
        return &obj->cmd.node_cmd.connect.resp;
    } else {
        return NULL;
    }
}

static inline bool const * extract__node_cmd__connection_status(struct a_cmd_t const * obj) {
    if (obj &&
        (obj->cmd._tag == a_cmd_tag_node_cmd) &&
        (obj->cmd.node_cmd._tag == a_cmd_node_tag_connection_status) &&
        (obj->cmd.node_cmd.connection_status._tag == n_cmd_connection_status_tag_resp)) {
        return &obj->cmd.node_cmd.connection_status.resp.connected;
    } else {
        return NULL;
    }
}

static inline struct n_connection const * extract__node_cmd__sleep(struct a_cmd_t const * obj) {
    if (obj &&
        (obj->cmd._tag == a_cmd_tag_node_cmd) &&
        (obj->cmd.node_cmd._tag == a_cmd_node_tag_sleep) &&
        (obj->cmd.node_cmd.sleep._tag == n_cmd_sleep_tag_resp) &&
        (obj->cmd.node_cmd.sleep.resp._tag == n_cmd_sleep_resp_tag_connection)) {
        return &obj->cmd.node_cmd.sleep.resp.connection;
    } else {
        return NULL;
    }
}

static inline struct a_resp_get_atom_info const * extract__config_cmd__get_atom_info(struct a_cmd_t const * obj) {
    if (obj &&
        (obj->cmd._tag == a_cmd_tag_config_cmd) &&
        (obj->cmd.config_cmd._tag == a_cmd_config_tag_get_atom_info) &&
        (obj->cmd.config_cmd.get_atom_info._tag == a_cmd_config_get_atom_info_tag_resp)) {
        return &obj->cmd.config_cmd.get_atom_info.resp;
    } else {
        return NULL;
    }
}

static inline struct n_send_resp const * extract__node_cmd__node_send(struct a_cmd_t const * obj) {
    if (obj &&
        (obj->cmd._tag == a_cmd_tag_node_cmd) &&
        (obj->cmd.node_cmd._tag == a_cmd_node_tag_send) &&
        (obj->cmd.node_cmd.send._tag == n_cmd_send_tag_resp)) {
        return &obj->cmd.node_cmd.send.resp;
    } else {
        return NULL;
    }
}

static inline struct n_cmd_poll_data_resp const * extract__node_cmd__poll_data(struct a_cmd_t const * obj) {
    if (obj &&
        (obj->cmd._tag == a_cmd_tag_node_cmd) &&
        (obj->cmd.node_cmd._tag == a_cmd_node_tag_poll_data) &&
        (obj->cmd.node_cmd.poll_data._tag == n_cmd_poll_data_tag_resp)) {
        return &obj->cmd.node_cmd.poll_data.resp;
    } else {
        return NULL;
    }
}

#endif /* AM_ATOM_API_EXTRACTORS_H */
