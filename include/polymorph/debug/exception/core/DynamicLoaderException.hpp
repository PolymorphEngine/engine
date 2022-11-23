/*
** EPITECH PROJECT, 2020
** DynamicLoaderException.hpp
** File description:
** header for DynamicLoaderException.c
*/


#pragma once

#include "polymorph/debug/exception/ExceptionLogger.hpp"

namespace polymorph::engine::debug
{
    class DynamicLoaderException : public ExceptionLogger
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            DynamicLoaderException(std::string symbol, std::string libPath, Logger::severity level = Logger::MAJOR);

            ~DynamicLoaderException() override = default;

//////////////////////--------------------------/////////////////////////

    };
}