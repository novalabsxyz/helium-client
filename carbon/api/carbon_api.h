#ifndef CARBON_API_H
#define CARBON_API_H

#include "helium_atom_api_types.h"
#include "helium_atom_api_infodefines.h"
#include "helium_atom_api_descriptors.h"

#include "xfer/carbon_xfer.h"
#include "carbon_interface.h"

#define ATOM_API_TYPE_ITER_COUNT (SCHEMA_DEPTH_helium_atom_api)

enum carbon_api_status {
    carbon_api_status_ok,
    carbon_api_status_err_xfer,
    carbon_api_status_err_timeout,
    carbon_api_status_err_wrong_seq,
    carbon_api_status_err_bad_frame,
    carbon_api_status_err_bad_cauterize,
};

struct carbon_api_ctx {
    union {
        struct type_encode_iterator encode[ATOM_API_TYPE_ITER_COUNT];
        struct type_decode_iterator decode[ATOM_API_TYPE_ITER_COUNT];
        struct type_size_iterator size[ATOM_API_TYPE_ITER_COUNT];
    } tis;

    /* The driver interface for transport layer concerns. */
    struct carbon_transport_iface const * iface;
};

/**
 * carbon_api
 *
 * Send the request stored in `req_res` to the Atom. The response will
 * be populated in the exact same memory location. */
enum carbon_api_status carbon_api(struct carbon_api_ctx * ctx, struct a_cmd_t * req_res);

#endif /* CARBON_API_H */
