#include "include/paddr.h"
#include "include/types.h"
#include "include/utils.h"

#include "include/control.h"

void control_reset_dev(bool reset, int dev) {
    control_cfg *cfg = (control_cfg *)CONTROL_OFFSET;
    if (reset)
        cfg->ip_reset |= BITN(dev);
    else
        cfg->ip_reset ^= BITN(dev);
    _AGX_SYNC_
}

void control_gate_dev_bus(bool open, int dev) {
    control_cfg *cfg = (control_cfg *)CONTROL_OFFSET;
    if (open)
        cfg->bus_gate |= BITN(dev);
    else
        cfg->bus_gate ^= BITN(dev);
    _AGX_SYNC_
}

void control_cycle_dev_wbus(bool cold, int dev_reset, int dev_bus) {
    if (cold) {
        control_gate_dev_bus(true, dev_bus);
        delay(1);
    }
    control_gate_dev_bus(false, dev_bus);
    control_reset_dev(true, dev_reset);
    delay(1);
    control_reset_dev(false, dev_reset);
    control_gate_dev_bus(true, dev_bus);
    if (cold)
        delay(1);
}