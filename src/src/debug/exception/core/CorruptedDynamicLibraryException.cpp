/*
** EPITECH PROJECT, 2020
** DynamicLoaderException.cpp
** File description:
** header for DynamicLoaderException.c
*/

#include "polymorph/engine/debug/exception/core/CorruptedDynamicLibraryException.hpp"


polymorph::engine::debug::CorruptedDynamicLibraryException::CorruptedDynamicLibraryException(std::string libPath, std::string error, Logger::severity level)
        : CoreException("Cannot open dynamic library at path : " + libPath + ", error : " + error, level)
{

}
