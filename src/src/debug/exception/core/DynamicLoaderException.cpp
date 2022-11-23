/*
** EPITECH PROJECT, 2020
** DynamicLoaderException.cpp
** File description:
** header for DynamicLoaderException.c
*/

#include "DynamicLoaderException.hpp"
#include "polymorph/debug/exception/core/DynamicLoaderException.hpp"


polymorph::engine::debug::DynamicLoaderException::DynamicLoaderException(std::string symbol, std::string libPath, Logger::severity level)
        : ExceptionLogger("[DynamicLoader] Failed to find symbol: " + symbol + " in library: " + libPath, level)
{

}
