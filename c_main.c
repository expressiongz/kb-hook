#include <stdio.h>
#include <windows.h>
HHOOK hook;
LRESULT CALLBACK LL_KB_Hook(int n_code, WPARAM kb_message, LPARAM lparam) {
    KBDLLHOOKSTRUCT* kbhook_struct = (KBDLLHOOKSTRUCT*)lparam;
    if(n_code == 0) {
        if(kb_message == WM_KEYDOWN) {
            printf("Hooked Key Down: %c\n", (char)(kbhook_struct->vkCode));
        }
    }
    return CallNextHookEx(hook, n_code, kb_message, lparam);
}

int main() {
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, LL_KB_Hook, 0, 0);
    MSG msg;
    while(!GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg); 
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hook);
    return 0;
}
