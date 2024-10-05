#include "include/paddr.h"
#include "include/rgn_rpc.h"

void c_RESET(void) {
    *(volatile uint32_t*)RGN_RPC_COMBUF_OFFSET |= 0xBABE;
    while (1) {
        rpc_loop();
    }
}

