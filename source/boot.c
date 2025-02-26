#include "include/paddr.h"
#include "include/rgn_rpc.h"
#include "include/control.h"

void c_RESET(void) {
    *(volatile uint32_t*)RGN_RPC_COMBUF_OFFSET |= 0xBABE;
    //control_reset_dev(true, CONTROL_IP_RESET_DEV_SC);
    if (!control_get_bus_gate(CONTROL_BUS_GATE_DEV_KIRK))
        control_cycle_dev_wbus(true, CONTROL_IP_RESET_DEV_KIRK, CONTROL_BUS_GATE_DEV_KIRK);
    while (1) {
        rpc_loop();
    }
}

