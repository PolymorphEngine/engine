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
    class DynamicLoaderException : public CoreException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            DynamicLoaderException(std::string symbol, std::string libPath, Logger::severity level = Logger::MAJOR);

            ~DynamicLoaderException() override = default;

//////////////////////--------------------------/////////////////////////

    };
}