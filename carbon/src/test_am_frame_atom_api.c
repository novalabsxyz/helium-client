#include "test_am_frame_atom_api.h"

#include "am.h"
#include "am_frame_atom_api.h"
#include "am_interface_host.h"

TEST test_the_link_thing_works(void) {
    struct am_ctx ctx;
    enum amf_atom_api_status aastat;

    SKIP();

    am_init(&ctx, &am_transport_iface_host);
    aastat = amf_atom_api(&ctx.aactx, &ctx.cmd);
    ASSERT_EQ_FMT(amfaa_status_ok, aastat, "%d");

    PASS();
}

SUITE(suite_am_frame_atom_api) {
    RUN_TEST(test_the_link_thing_works);
}
