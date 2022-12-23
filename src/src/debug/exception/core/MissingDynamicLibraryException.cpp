/*
** EPITECH PROJECT, 2020
** DynamicLoaderException.cpp
** File description:
** header for DynamicLoaderException.c
*/

#include "polymorph/engine/debug/exception/core/MissingDynamicLibraryException.hpp"


polymorph::engine::debug::MissingDynamicLibraryException::MissingDynamicLibraryException(std::string libPath, Logger::severity level)
        : CoreException("No dynamic library at path : " + libPath, level)
{

}
