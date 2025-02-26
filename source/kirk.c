#include "include/types.h"
#include "include/utils.h"
#include "include/paddr.h"

#include "include/kirk.h"

int kirk_simpleCmd(int cmd, uint32_t src, uint32_t dst) {
    kirk_ctrl *ctrl = (kirk_ctrl *)KIRK_OFFSET;
    int ret;
    {
        ctrl->cmd = cmd;
        ctrl->src = src & 0x1FFFFFFF;
        ctrl->dst = dst & 0x1FFFFFFF;
        ctrl->trig = 1;
    }
    do {
        ret = ctrl->status;
    } while (!(ret & 0x11));
    ctrl->status_ack = ret & 0x11;
    if (!(ret & 0x10))
        return ctrl->res | (ctrl->err << 16);

    /* cleanup?
    {
        ctrl->trig = 2;
        do {
            ret = ctrl->status;
        } while (!(ret & 2));
        ctrl->status_ack = ret & 2;
        _AGX_SYNC_
    }*/

    return -1;
}