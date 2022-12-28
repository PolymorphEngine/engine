/*
** EPITECH PROJECT, 2022
** DynamicLoader.cpp by 0xMemoryGrinder
** File description:
** DynamicLoader.cpp
*/

#include <filesystem>
#include "polymorph/engine/api/DynamicLoader.hpp"
#include "polymorph/engine/debug/exception/core/MissingDynamicLibraryException.hpp"
#include "polymorph/engine/debug/exception/core/CorruptedDynamicLibraryException.hpp"

polymorph::engine::api::DynamicLoader::DynamicLoader(DynamicLoader &&ref) noexcept
        : _handler(ref._handler), _libPath(ref._libPath)
{
    ref._handler = nullptr;
}

polymorph::engine::api::DynamicLoader::~DynamicLoader()
{
    if (_handler != nullptr)
        _closeHandle();
    _handler = nullptr;
}

#ifdef _WIN32
std::string GetLastErrorStdStr()
{
    DWORD error = GetLastError();
    if (error)
    {
        LPVOID lpMsgBuf;
        DWORD bufLen = FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                error,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR) &lpMsgBuf,
                0, NULL );
        if (bufLen)
        {
            LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
            std::string result(lpMsgStr, lpMsgStr+bufLen);

            LocalFree(lpMsgBuf);

            return result;
        }
    }
    return std::string();
}
#endif

void polymorph::engine::api::DynamicLoader::loadHandler(const std::string &libPath)
{
    if (_handler != nullptr)
        _closeHandle();

#if _WIN32
    _handler = LoadLibrary(TEXT(libPath.c_str()));
#else
    _handler = dlopen(libPath.c_str(), RTLD_LAZY);
#endif

    if (_handler == nullptr) {
        if (std::filesystem::exists(libPath))
            throw debug::MissingDynamicLibraryException(libPath);
#if _WIN32
        throw debug::CorruptedDynamicLibraryException(libPath, GetLastErrorStdStr());
#else
        throw debug::CorruptedDynamicLibraryException(libPath, dlerror());
#endif
    }
    _libPath = libPath;
}

void polymorph::engine::api::DynamicLoader::_closeHandle()
{
#if _WIN32
    FreeLibrary((HMODULE)_handler);
#else
    dlclose(_handler);
#endif
}
