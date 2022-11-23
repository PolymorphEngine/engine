/*
** EPITECH PROJECT, 2022
** DynamicLoader.cpp by 0xMemoryGrinder
** File description:
** DynamicLoader.cpp
*/

#include <filesystem>
#include "polymorph/api/DynamicLoader.hpp"
#include "polymorph/debug/exception/config/CorruptedFileException.hpp"
#include "polymorph/debug/exception/core/MissingDynamicLibraryException.hpp"

polymorph::engine::api::DynamicLoader::DynamicLoader(DynamicLoader &&ref) noexcept
        : _handler(ref._handler), _libPath(ref._libPath)
{
    ref._handler = nullptr;
}

polymorph::engine::api::DynamicLoader::~DynamicLoader()
{
    if (_handler != nullptr)
        closeHandle();
    _handler = nullptr;
}

void polymorph::engine::api::DynamicLoader::loadHandler(const std::string &libPath)
{
    if (_handler != nullptr)
        closeHandle();

#if _WIN32
    _handler = LoadLibrary(TEXT(libPath.c_str()));
#else
    _handler = dlopen(libPath.c_str(), RTLD_LAZY);
#endif

    if (_handler == nullptr) {
        if (std::filesystem::exists(libPath))
            throw debug::MissingDynamicLibraryException("[DynamicLoader] No dynamic library at path: " + libPath); // TODO: check parameters
        throw debug::CorruptedFileException("[DynamicLoader] Failed to open dynamic library at path: " + libPath + ", error: " + dlerror()); //TODO: check parameters
    }
    _libPath = libPath;
}

void polymorph::engine::api::DynamicLoader::closeHandle()
{
#if _WIN32
    FreeLibrary((HMODULE)_handler);
#else
    dlclose(_handler);
#endif
}
