/*
** EPITECH PROJECT, 2020
** NoScenesFoundException.cpp
** File description:
** header for NoScenesFoundException.c
*/

#include "polymorph/debug/exception/core/NoScenesFoundException.hpp"


polymorph::engine::debug::NoScenesFoundException::NoScenesFoundException(Logger::severity level)
        : ExceptionLogger("[NoScenesFoundException] No scenes found in the project", level) {}
