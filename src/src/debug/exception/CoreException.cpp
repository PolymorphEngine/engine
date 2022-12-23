/*
** EPITECH PROJECT, 2020
** CoreException.cpp
** File description:
** header for CoreException.c
*/

#include "polymorph/engine/debug/exception/CoreException.hpp"

polymorph::engine::debug::CoreException::CoreException(std::string message,
polymorph::engine::debug::Logger::severity level)
        : ExceptionLogger("[CoreException] " + message, level)
{

}
