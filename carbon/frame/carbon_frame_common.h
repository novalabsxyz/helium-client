#ifndef CARBON_FRAME_COMMON_H
#define CARBON_FRAME_COMMON_H

enum carbon_frame_ctl_byte {
    SOF_CHAR = 0xA3,            /* start-of-frame */
    EOF_CHAR = 0xA4,            /* end-of-frame */
    ESC_CHAR = 0x1B,            /* escape char */

    SOF_ESC = 0x01,             /* SOF escape value */
    EOF_ESC = 0x02,             /* EOF escape value */
    ESC_ESC = 0x03,             /* ESC escape value */
};

#endif /* CARBON_FRAME_COMMON_H */
