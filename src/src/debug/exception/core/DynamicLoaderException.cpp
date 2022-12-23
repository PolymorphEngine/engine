/*
** EPITECH PROJECT, 2020
** DynamicLoaderException.cpp
** File description:
** header for DynamicLoaderException.c
*/

#include "polymorph/engine/debug/exception/core/DynamicLoaderException.hpp"


polymorph::engine::debug::DynamicLoaderException::DynamicLoaderException(std::string symbol, std::string libPath, Logger::severity level)
        : CoreException("Failed to find symbol: " + symbol + " in library: " + libPath, level)
{

}
