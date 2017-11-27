struct WINDOWCOMPOSITIONATTRIBUTE {
    DWORD   dwAttribute; // 16
    LPCVOID pValue;      // TRUE
    DWORD   cbAttribute; // 4
};
typedef HRESULT
(__stdcall *funcSetWindowCompositionAttribute)(
    HWND hwnd,
    WINDOWCOMPOSITIONATTRIBUTE* pwca
    );

template<typename ApiPrototype>
class WINAPI_STUB
{
public:
    typedef ApiPrototype proto;
    static ApiPrototype call;
    const WINAPI_STUB* operator->() { return this; }

    static void initialize(LPCTSTR module, LPCSTR name) {
        HMODULE hModule = GetModuleHandle(module);
        call = (ApiPrototype)GetProcAddress(hModule, name);
    }
};
template<typename ApiPrototype>
ApiPrototype WINAPI_STUB<ApiPrototype>::call;

void* tipwin_create(HWND hwnd)
{
    WINDOWCOMPOSITIONATTRIBUTE wca;
    wca.dwAttribute = 16;
    BOOL val = TRUE;
    wca.pValue = &val;
    wca.cbAttribute = 4;

    WINAPI_STUB<funcSetWindowCompositionAttribute> SetWindowCompositionAttribute;
    SetWindowCompositionAttribute.initialize(_T("user32.dll"), "SetWindowCompositionAttribute");
    if (SetWindowCompositionAttribute.call) {
        SetWindowCompositionAttribute.call(hwnd, &wca);
    }
}
