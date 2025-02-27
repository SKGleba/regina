#include <include/types.h>

#include <include/utils.h>
#include <include/clib.h>
#include <include/paddr.h>
#include <include/kirk.h>
#include <include/control.h>

#define WORKBUF_PADDR 0xbfc00a00
#define WORKBUF_SIZE 0x100

__attribute__((section(".text.third")))
int test_kirk456789(void *data, uint32_t size, uint8_t cmd, uint8_t keyslot) {
    void *workbuf = (void *)WORKBUF_PADDR;
    memset(workbuf, 0, WORKBUF_SIZE);
    if (((size * 2) + 0x34) > WORKBUF_SIZE)
        return -1;
    v32p workbuf = 4;
    if (cmd > 6)
        v32p workbuf = 5;
    if ((cmd == 4) || (cmd == 7))
        v8p(workbuf + 0xC) = keyslot;
    else
        v8p(workbuf + 0xD) = ((cmd == 5) || (cmd == 8)) ? 1 : 2;
    v32p(workbuf + 0x10) = size;
    if ((cmd == 6) || (cmd == 9))
        memcpy(workbuf + ((cmd == 9) ? 0x34 : 0x24), data, size);
    else
        memcpy(workbuf + 0x14, data, size);
    return kirk_simpleCmd(cmd, WORKBUF_PADDR, (uint32_t)data);
}

__attribute__((section(".text.rpcp")))
int rpcp(uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t* extra_data) {
    return test_kirk456789((void *)arg0, arg1, arg2 & 0xFF, (arg2 >> 8) & 0xFF);
}