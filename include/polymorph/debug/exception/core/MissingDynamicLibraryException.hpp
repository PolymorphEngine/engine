/*
** EPITECH PROJECT, 2020
** DynamicLoaderException.hpp
** File description:
** header for DynamicLoaderException.c
*/


#pragma once

#include "polymorph/debug/exception/CoreException.hpp"

namespace polymorph::engine::debug
{
    class MissingDynamicLibraryException : public CoreException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            MissingDynamicLibraryException(std::string libPath, Logger::severity level = Logger::MAJOR);

            ~MissingDynamicLibraryException() override = default;

//////////////////////--------------------------/////////////////////////

    };
}