#include <windows.h>
#include <iostream>

// Define the IMyInterface
struct IMyInterface : public IUnknown {
    virtual HRESULT STDMETHODCALLTYPE Method16(int param1, BSTR param2) = 0;
};

// Implement the interface
class MyInterfaceImpl : public IMyInterface {
public:
    // IUnknown methods
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override {
        if (riid == IID_IUnknown || riid == __uuidof(IMyInterface)) {
            *ppvObject = static_cast<IMyInterface*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }

    ULONG STDMETHODCALLTYPE AddRef() override {
        return InterlockedIncrement(&refCount);
    }

    ULONG STDMETHODCALLTYPE Release() override {
        ULONG res = InterlockedDecrement(&refCount);
        if (res == 0) {
            delete this;
        }
        return res;
    }

    // IMyInterface method
    HRESULT STDMETHODCALLTYPE Method16(int param1, BSTR param2) override {
        wprintf(L"Method16 called with param1: %d, param2: %s\n", param1, param2);
        return S_OK;
    }

private:
    LONG refCount = 1;
};

int main() {
    IMyInterface* myInterface = new MyInterfaceImpl();

    // Call Method16
    BSTR bstr = SysAllocString(L"Hello, COM!");
    myInterface->Method16(42, bstr);
    SysFreeString(bstr);

    // Release the interface
    myInterface->Release();

    return 0;
}
