#ifndef AM_FRAME_ATOM_API_H
#define AM_FRAME_ATOM_API_H

#include "helium_atom_api_types.h"
#include "helium_atom_api_infodefines.h"
#include "helium_atom_api_descriptors.h"

#include "am_driver_transport.h"
#include "am_interface.h"

#define ATOM_API_TYPE_ITER_COUNT (SCHEMA_DEPTH_helium_atom_api)

enum amf_atom_api_status {
    amfaa_status_ok,
    amfaa_status_err_timeout,
    amfaa_status_err_wrong_seq,
    amfaa_status_err_bad_frame,
    amfaa_status_err_bad_cauterize,
};

struct amfaa_ctx {
    union {
        struct type_encode_iterator encode[ATOM_API_TYPE_ITER_COUNT];
        struct type_decode_iterator decode[ATOM_API_TYPE_ITER_COUNT];
        struct type_size_iterator size[ATOM_API_TYPE_ITER_COUNT];
    } tis;

    /* The driver interface for transport layer concerns. */
    struct am_transport_iface const * iface;
};

/**
 * amf_atom_api
 *
 * Send the request stored in `req_res` to the Atom. The response will
 * be populated in the exact same memory location. */
enum amf_atom_api_status amf_atom_api(struct amfaa_ctx * ctx, struct a_cmd_t * req_res);

#endif /* AM_FRAME_ATOM_API_H */
