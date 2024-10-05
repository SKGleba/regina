#include "include/rgn_rpc.h"

#include "include/types.h"
#include "include/utils.h"
#include "include/paddr.h"
#include "include/clib.h"

void rpc_loop(void) {
    uint8_t chash;
    rgn_rpc_combuf_s *combuf = (rgn_rpc_combuf_s *)RGN_RPC_COMBUF_OFFSET;
    combuf->cmd.magic = 0;
    combuf->cmd.hash = 0;
    combuf->rpc_status = RGN_RPC_STATUS_READY;
    while (true) {
        if (combuf->cmd.magic != RGN_RPC_CMD_MAGIC) {
            delay(RGN_RPC_DELAY);
            continue;
        }

        combuf->rpc_status = RGN_RPC_STATUS_PARSE;
        chash = 0;
        for (int i = 0; i < 0x11; i++)
            chash += ((uint8_t *)&combuf->cmd.id)[i];
        if (chash != combuf->cmd.hash) {
            delay(RGN_RPC_DELAY);
            continue;
        }

        combuf->rpc_status = RGN_RPC_STATUS_INCMD;
        switch (combuf->cmd.id) {
        case RGN_RPC_CMD_NOP:
            combuf->ret = get_build_timestamp();
            break;
        case RGN_RPC_CMD_READ32:
            combuf->ret = vp combuf->args[0];
            break;
        case RGN_RPC_CMD_WRITE32:
            vp(combuf->args[0]) = combuf->args[1];
            combuf->ret = 0;
            break;
        case RGN_RPC_CMD_MEMSET:
            combuf->ret = (uint32_t)memset((void *)combuf->args[0], combuf->args[1] & 0xFF, combuf->args[2]);
            break;
        case RGN_RPC_CMD_MEMCPY:
            combuf->ret = (uint32_t)memcpy((void *)combuf->args[0], (void *)combuf->args[1], combuf->args[2]);
            break;
        case RGN_RPC_CMD_MEMSET32:
            combuf->ret = (uint32_t)memset32((void *)combuf->args[0], combuf->args[1], combuf->args[2]);
            break;
        default:
            combuf->ret = -1;
            break;
        }

        combuf->rpc_status = RGN_RPC_STATUS_REPLY;
        while (combuf->cmd_packed)
            delay(RGN_RPC_DELAY);
        
        combuf->rpc_status = RGN_RPC_STATUS_READY;
    }
}