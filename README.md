# regina
RPC server for Playstation Vita's Allegrex "pspemu" processor<br>
It is intended to be used as a companion to [bob](https://github.com/SKGleba/bob) for research and reverse engineering of the Playstation Vita video game console.

## loading regina (warmboot)
[This psp2spl sample](https://github.com/SKGleba/psp2spl/tree/master/samples/pspemu_brom_exec) can be used to load regina. <br>
[Bob](https://github.com/SKGleba/bob) can also load it using regina_loadRegina() / RPC_CMD_LOAD_REGINA

## interacting with regina
By default Regina listens for commands at BOOTRAM+0xfc0, see [rgn_rpc.h](source/include/rgn_rpc.h) for details and [Bob](https://github.com/SKGleba/bob)'s regina_sendCmd() for example usage.<br>
On ARM/f00d side BOOTRAM is mapped to 0xE8100000, ARM access can be unlocked by setting the appropriate bit in REGBUS::REGBUS_AGX_SRAM_ACL