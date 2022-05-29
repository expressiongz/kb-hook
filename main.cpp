#include <windows.h>
#include <iostream>
HHOOK hook = nullptr;
LRESULT __stdcall LL_KB_Hook(int n_code, WPARAM kb_message, LPARAM lparam) {
    const auto* p_kbd_hookstruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lparam);
    if (n_code == HC_ACTION && kb_message == WM_KEYDOWN) {
        std::printf("Hooked Key Down: %c\n", p_kbd_hookstruct->vkCode);
    }
    return CallNextHookEx(hook, n_code, kb_message, lparam);
}

int main() {
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, LL_KB_Hook, 0, 0);
    MSG msg;
    while (!GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hook);
    return 0;
}
