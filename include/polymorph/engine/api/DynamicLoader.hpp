/*
** EPITECH PROJECT, 2020
** DynamicLoader.hpp by 0xMemoryGrinder
** File description:
** DynamicLoader.hpp
*/

#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "polymorph/engine/debug/exception/core/DynamicLoaderException.hpp"

#ifdef _WIN32
    #define MMNOSOUND
    #define NOGDICAPMASKS     // CC_*, LC_*, PC_*, CP_*, TC_*, RC_
    #define NOVIRTUALKEYCODES // VK_*
    #define NOWINMESSAGES     // WM_*, EM_*, LB_*, CB_*
    #define NOWINSTYLES       // WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
    #define NOSYSMETRICS      // SM_*
    #define NOMENUS           // MF_*
    #define NOICONS           // IDI_*
    #define NOKEYSTATES       // MK_*
    #define NOSYSCOMMANDS     // SC_*
    #define NORASTEROPS       // Binary and Tertiary raster ops
    #define NOSHOWWINDOW      // SW_*
    #define OEMRESOURCE       // OEM Resource values
    #define NOATOM            // Atom Manager routines
    #define NOCLIPBOARD       // Clipboard routines
    #define NOCOLOR           // Screen colors
    #define NOCTLMGR          // Control and Dialog routines
    #define NODRAWTEXT        // DrawText() and DT_*
    #define NOGDI             // All GDI defines and routines
    #define NOKERNEL          // All KERNEL defines and routines
    #define NOUSER
    //#define NONLS             // All NLS defines and routines
    #define NOMB              // MB_* and MessageBox()
    #define NOMEMMGR          // GMEM_*, LMEM_*, GHND, LHND, associated routines
    #define NOMETAFILE        // typedef METAFILEPICT
    #define NOMINMAX          // Macros min(a,b) and max(a,b)
    #define NOMSG             // typedef MSG and associated routines
    #define NOOPENFILE        // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
    #define NOSCROLL          // SB_* and scrolling routines
    #define NOSERVICE         // All Service Controller routines, SERVICE_ equates, etc.
    #define NOSOUND           // Sound driver routines
    #define NOTEXTMETRIC      // typedef TEXTMETRIC and associated routines
    #define NOWH              // SetWindowsHook and WH_*
    #define NOWINOFFSETS      // GWL_*, GCL_*, associated routines
    #define NOCOMM            // COMM driver routines
    #define NOKANJI           // Kanji support stuff.
    #define NOHELP            // Help engine interface.
    #define NOPROFILER        // Profiler interface.
    #define NODEFERWINDOWPOS  // DeferWindowPos routines
    #define NOMCX             // Modem Configuration Extensions

    #include <Windows.h>

    #undef near
    #undef far
#else
    #include <dlfcn.h> //dlopen

#include "polymorph/engine/debug/exception/core/DynamicLoaderException.hpp"

#endif

namespace polymorph::engine::api
{

    class DynamicLoader
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////

        public:
            DynamicLoader() = default;

            DynamicLoader(const DynamicLoader&) = delete;
            DynamicLoader(DynamicLoader&&) noexcept;

            ~DynamicLoader();


//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        protected:
#ifdef _WIN32
            /**
             * @property _handler pointer to opened dynamic library
             */
            HINSTANCE _handler = nullptr;
#else
            /**
             * @property _handler pointer to opened dynamic library
             */
            void *_handler = nullptr;
#endif

            /**
             * @property _libPath path to the dynamic library
             */
            std::string _libPath;


//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            /**
             * @details Close the previous opened library (if one is open) and opens the one passed as parameter
             * @param libPath
             * @throws MissingDynamicLibraryException if the library does not exists at the provided path
             * @throws CorruptedDynamicLibraryException if the library cannot be opened
             */
            void loadHandler(const std::string &libPath);

            /**
             * @brief Search for a symbol in the opened library and if found, return it with the specified type signature
             * @tparam T type of the symbol to return (generally a function pointer)
             * @param name name of the symbol to search for
             * @param no_except if true, the function will return a nullptr if the symbol is not found and not throw an exception
             * @throws DynamicLoaderException if the symbol is not found and no_except is false
             * @return the symbol with the specified type signature
             */
            template<typename T>
            T loadSymbol(std::string name, bool no_except = false)
            {
#ifdef _WIN32
                T s = (T) GetProcAddress(_handler, name.c_str());
#else
                void *s = dlsym(_handler, name.c_str());
#endif
                if (s == nullptr && !no_except)
                    throw debug::DynamicLoaderException(name, _libPath);
                return reinterpret_cast<T>(s);
            }

        protected:
            void _closeHandle();


//////////////////////--------------------------/////////////////////////

    };
}
