#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "types.h"
#include "paddr.h"
#include "utils.h"

#define reg volatile uint32_t

struct _control_cfg {
    reg excfg[0x10];
    reg opt;
    reg core2_rpc;
    reg core2_lock;
    reg ip_reset;
    reg bus_gate;
    reg clk_gate;
    reg clk_gate2;
    reg clk_sel;
    reg clk_sel2;
    reg clk_sel_spi;
    reg clk_ext;
    reg avc_pwr;
    reg unk_0x74;
    reg io_ext;
    reg gpio_ctl;
    reg usb_ctl;
    reg unk_0x84[0x1f];
};
typedef struct _control_cfg control_cfg;

enum CONTROL_IP_RESET_DEV {
    CONTROL_IP_RESET_DEV_EMCTOP = 0,
    CONTROL_IP_RESET_DEV_SC,
    CONTROL_IP_RESET_DEV_CORE2,
    CONTROL_IP_RESET_DEV_AW,
    CONTROL_IP_RESET_DEV_VME,
    CONTROL_IP_RESET_DEV_AVC,
    CONTROL_IP_RESET_DEV_USB0,
    CONTROL_IP_RESET_DEV_ATA0,
    CONTROL_IP_RESET_DEV_MSIF0,
    CONTROL_IP_RESET_DEV_MSIF1,
    CONTROL_IP_RESET_DEV_KIRK,
    CONTROL_IP_RESET_DEV_ATA1 = 12,
    CONTROL_IP_RESET_DEV_USB1
};

enum CONTROL_BUS_GATE_DEV {
    CONTROL_BUS_GATE_DEV_ME = 0,
    CONTROL_BUS_GATE_DEV_AW_A,
    CONTROL_BUS_GATE_DEV_AW_B,
    CONTROL_BUS_GATE_DEV_AW_EDRAM,
    CONTROL_BUS_GATE_DEV_DMAC0,
    CONTROL_BUS_GATE_DEV_DMAC1,
    CONTROL_BUS_GATE_DEV_DMAC2,
    CONTROL_BUS_GATE_DEV_KIRK,
    CONTROL_BUS_GATE_DEV_ATA0,
    CONTROL_BUS_GATE_DEV_USB0,
    CONTROL_BUS_GATE_DEV_MSIF0,
    CONTROL_BUS_GATE_DEV_MSIF1,
    CONTROL_BUS_GATE_DEV_EMCDDR,
    CONTROL_BUS_GATE_DEV_EMCSM,
    CONTROL_BUS_GATE_DEV_APB,
    CONTROL_BUS_GATE_DEV_AUDIO0,
    CONTROL_BUS_GATE_DEV_AUDIO1,
    CONTROL_BUS_GATE_DEV_ATA1,
    CONTROL_BUS_GATE_DEV_USB1
};

void control_reset_dev(bool reset, int dev);
void control_gate_dev_bus(bool open, int dev);
void control_cycle_dev_wbus(bool cold, int dev_reset, int dev_bus);

#define control_get_reset(dev) (!!(((control_cfg *)CONTROL_OFFSET)->ip_reset & BITN((dev))))
#define control_get_bus_gate(dev) (!!(((control_cfg *)CONTROL_OFFSET)->bus_gate & BITN((dev))))

#endif