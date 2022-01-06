#include <iostream>
#include <Windows.h>
HHOOK hook;

LRESULT CALLBACK LLKB_HOOK(int p_code, WPARAM wParam, LPARAM lParam){
  KBDLLHOOKSTRUCT* kb_struct = (KBDLLHOOKSTRUCT*)lParam;

  if(p_code == HC_ACTION){
    std::cout << "Hooked Key Press: " << (char)(kb_struct->vkCode) << "\n";
  }
  return CallNextHookEx(hook, p_code, wParam, lParam);
}

int main(){
  hook = SetWindowsHookEx(WH_KEYBOARD_LL, LLKB_HOOK, 0, 0);

  MSG msg;
  while(!GetMessage(&msg, NULL, 0, 0)){
    TranslateMessage(&msg);
    DispatchMessage(&msg);

  }
  UnhookWindowsHookEx(hook);
  return 0;
}