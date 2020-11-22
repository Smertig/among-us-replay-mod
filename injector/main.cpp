#include <iostream>
#include <string_view>
#include <optional>
#include <array>
#include <filesystem>
#include <sstream>

#include <Windows.h>
#include <TlHelp32.h>
#include <psapi.h>

class error_message {
    std::stringstream m_stream;

public:
    ~error_message() {
        ::MessageBoxA(nullptr, m_stream.str().c_str(), "Injector", MB_ICONERROR);
    }

    template <class T>
    error_message& operator<<(const T& value) {
        m_stream << value;
        std::cerr << value;
        return *this;
    }
};

std::optional<DWORD> find_process(std::string_view name) {
    HANDLE snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    PROCESSENTRY32 process_entry{};
    process_entry.dwSize = sizeof(process_entry);

    std::optional<DWORD> result;

    if (Process32First(snapshot, &process_entry) == TRUE) {
        do {
            if (process_entry.szExeFile == name) {
                result = process_entry.th32ProcessID;
                break;
            }
        } while (Process32Next(snapshot, &process_entry) == TRUE);
    }

    ::CloseHandle(snapshot);
    return result;
}

bool process_has_dll(HANDLE process_handle, std::string_view dll_path) {
    std::array<HMODULE, 1024> modules;

    // Get a list of all the modules in this process.
    DWORD out_size = 0;
    if (!EnumProcessModules(process_handle, modules.data(), sizeof(modules), &out_size)) {
        return false;
    }

    for (std::size_t i = 0; i < out_size / sizeof(HMODULE); i++) {
        std::array<char, MAX_PATH> module_name{};

        // Get the full path to the module's file.
        if (GetModuleFileNameExA(process_handle, modules[i], module_name.data(), module_name.size())) {
            if (std::filesystem::path(module_name.data()).filename() == std::filesystem::path(dll_path).filename()) {
                return true;
            }
        }
    }

    return false;
}

const char* default_dll_name = "among-us-replay-mod.dll";
const char* default_process_name = "Among Us.exe";

void print_usage() {
    error_message{} << "usage: injector.exe [dll_path=\"" << default_dll_name << "\"] [process_name=\"" << default_process_name << "\"]\n";
}

int main(int argc, const char** argv) {
    using namespace std::string_view_literals;

    if (argc > 1 && (argv[1] == "-h"sv || argv[1] == "--help"sv)) {
        print_usage();
        return 1;
    }

    const char* short_dll_path = argc > 1 ? argv[1] : default_dll_name;
    const char* process_name = argc > 2 ? argv[2] : default_process_name;

    // get path of DLL
    std::array<char, MAX_PATH> dll_path{};
    ::GetFullPathNameA(short_dll_path, dll_path.size(), dll_path.data(), nullptr);

    std::cout << "injecting " << dll_path.data() << " into " << process_name << ".." << std::endl;

    // get process
    auto process_id = find_process(process_name);
    if (!process_id) {
        error_message{} << "unable to find process '" << process_name << "'\n";
        return 1;
    }

    HANDLE process_handle = ::OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, process_id.value());

    if (!process_has_dll(process_handle, dll_path.data())) {
        LPVOID allocated_memory = ::VirtualAllocEx(process_handle, nullptr, dll_path.size(), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

        ::WriteProcessMemory(process_handle, allocated_memory, dll_path.data(), dll_path.size(), nullptr);

        ::CreateRemoteThread(process_handle, nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, allocated_memory, 0, nullptr);

        ::MessageBoxA(nullptr, "Successfully injected", "Injector", MB_ICONINFORMATION);
    }
    else {
        error_message{} << "dll " << dll_path.data() << " is already loaded into '" << process_name << "'\n";
    }
    ::CloseHandle(process_handle);

    return 0;
}
