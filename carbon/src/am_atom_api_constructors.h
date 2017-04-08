#ifndef AM_ATOM_API_CONSTRUCTORS_H
#define AM_ATOM_API_CONSTRUCTORS_H

#include "helium_atom_api.h"
#include <assert.h>

static inline struct a_cmd_t * new__node_cmd__set_mode(struct a_cmd_t * obj,
                                                uint16_t seq,
                                                enum n_mode mode) {
    assert(obj);

    *obj = (struct a_cmd_t) {
        .sequence = seq,
        .cmd = {
            ._tag = a_cmd_tag_node_cmd,
            .node_cmd = {
                ._tag = a_cmd_node_tag_set_mode,
                .set_mode = {
                    ._tag = n_cmd_set_mode_tag_req,
                    .req = mode,
                },
            },
        },
    };

    return obj;
}

static inline struct a_cmd_t * new__node_cmd__connect__quick(struct a_cmd_t * obj,
                                                      uint16_t seq,
                                                      uint32_t utime,
                                                      struct n_connection const * connection) {
    assert(obj);
    assert(connection);

    *obj = (struct a_cmd_t) {
        .sequence = seq,
        .cmd = {
            ._tag = a_cmd_tag_node_cmd,
            .node_cmd = {
                ._tag = a_cmd_node_tag_connect,
                .connect = {
                    ._tag = n_cmd_connect_tag_req,
                    .req = {
                        ._tag = n_cmd_connect_req_tag_quick,
                        .quick = {
                            .time = utime,
                            .connection = *connection,
                        },
                    },
                },
            },
        },
    };

    return obj;
}

static inline struct a_cmd_t * new__node_cmd__connect__cold(struct a_cmd_t * obj,
                                                            uint16_t seq) {
    assert(obj);

    *obj = (struct a_cmd_t) {
        .sequence = seq,
        .cmd = {
            ._tag = a_cmd_tag_node_cmd,
            .node_cmd = {
                ._tag = a_cmd_node_tag_connect,
                .connect = {
                    ._tag = n_cmd_connect_tag_req,
                    .req = {
                        ._tag = n_cmd_connect_req_tag_cold,
                    }
                }
            },
        },
    };

    return obj;
}

static inline struct a_cmd_t * new__node_cmd__connection_status(struct a_cmd_t * obj,
                                                                uint16_t seq) {
    assert(obj);

    *obj = (struct a_cmd_t) {
        .sequence = seq,
        .cmd = {
            ._tag = a_cmd_tag_node_cmd,
            .node_cmd = {
                ._tag = a_cmd_node_tag_connection_status,
            },

        },
    };

    return obj;
}

static inline struct a_cmd_t * new__node_cmd__sleep(struct a_cmd_t * obj,
                                                    uint16_t seq) {
    assert(obj);

    *obj = (struct a_cmd_t) {
        .sequence = seq,
        .cmd = {
            ._tag = a_cmd_tag_node_cmd,
            .node_cmd = {
                ._tag = a_cmd_node_tag_sleep,
                .sleep = {
                    ._tag = n_cmd_sleep_tag_req,
                }
            },
        },
    };

    return obj;
}

static inline struct a_cmd_t * new__config_cmd__get_atom_info(struct a_cmd_t * obj,
                                                              uint16_t seq) {
    assert(obj);

    *obj = (struct a_cmd_t) {
        .sequence = seq,
        .cmd = {
            ._tag = a_cmd_tag_config_cmd,
            .config_cmd = {
                ._tag = a_cmd_config_tag_get_atom_info,
                .get_atom_info = {
                    ._tag = a_cmd_config_get_atom_info_tag_req,
                },
            },
        },
    };

    return obj;

}

#endif /* AM_ATOM_API_CONSTRUCTORS_H */
