import sys
import time
import bob_rpc

REGINA_RPC_COMMANDS = {
    "ping": "0x1",
    "read32": "0x2",
    "write32": "0x3",
    "memset": "0x4",
    "memcpy": "0x5",
    "memset32": "0x6",
    "kirk" : "0x7",
    "exec": "0x8"
}

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python regina_rpc.py <command> [arg0..arg5] [timeout_x] [timeout_y]")
        print("Available commands:", REGINA_RPC_COMMANDS.keys())
        sys.exit(1)

    uinput_argv = [sys.argv[1], "0x0", "0x0", "0x0", "0x0", "0x0", "0x0"]
    if sys.argv[1] in REGINA_RPC_COMMANDS:
        uinput_argv[0] = REGINA_RPC_COMMANDS[sys.argv[1]]
    for i in range(2, len(sys.argv)):
        uinput_argv[i - 1] = sys.argv[i]

    bob_rpc.silent_mode = 2
    bob_rpc.bert.silent_mode = 2

    print("RPC: " + " ".join(uinput_argv))

    try:
        resp = bob_rpc.handle_cmd("regina_cmd", uinput_argv)
    except KeyboardInterrupt:
        pass
    except Exception as e:
        print(e)

    print("REGINA: 0x" + bob_rpc.swapstr32(resp[8:16]))
    
    bob_rpc.bert.client.close()