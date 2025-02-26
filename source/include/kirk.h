#ifndef __KIRK_H__
#define __KIRK_H__

#include "types.h"

#define reg volatile uint32_t

struct _kirk_ctrl {
    reg sig;
    reg ver;
    reg err;
    reg trig;
    reg cmd;
    reg res;
    reg unk;
    reg status;
    reg status_async;
    reg status_async_ack;
    reg status_ack;
    reg src;
    reg dst;
};
typedef struct _kirk_ctrl kirk_ctrl;

enum KIRK_CMD {
    KIRK_CMD_BRAM_DECRYPT = 0,
    KIRK_CMD_IPL_DECRYPT,
    KIRK_CMD_DRMBB_RECRYPT,
    KIRK_CMD_DRMBB_DECRYPT,
    KIRK_CMD_KS_AES128_CBC_ENC,
    KIRK_CMD_KM_AES128_CBC_ENC,
    KIRK_CMD_RK_AES128_CBC_ENC,
    KIRK_CMD_KS_AES128_CBC_DEC,
    KIRK_CMD_KM_AES128_CBC_DEC,
    KIRK_CMD_RK_AES128_CBC_DEC,
    KIRK_CMD_DRMBB_VERIFY,
    KIRK_CMD_SHA1,
    KIRK_CMD_ECDSA_GEN,
    KIRK_CMD_ECDSA_MUL,
    KIRK_CMD_RNG,
    KIRK_CMD_RNG_RESEED,
    KIRK_CMD_ECDSA_SIGN,
    KIRK_CMD_ECDSA_VERIFY,
    KIRK_CMD_CRT_VERIFY
};

int kirk_simpleCmd(int cmd, uint32_t src, uint32_t dst);

#undef reg

#endif