/*
** EPITECH PROJECT, 2020
** DynamicLoaderException.hpp
** File description:
** header for DynamicLoaderException.c
*/


#pragma once

#include "polymorph/engine/debug/exception/CoreException.hpp"

namespace polymorph::engine::debug
{
    class CorruptedDynamicLibraryException : public CoreException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            CorruptedDynamicLibraryException(std::string libPath, std::string error, Logger::severity level = Logger::MAJOR);

            ~CorruptedDynamicLibraryException() override = default;

//////////////////////--------------------------/////////////////////////

    };
}