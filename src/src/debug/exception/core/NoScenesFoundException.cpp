/*
** EPITECH PROJECT, 2020
** NoScenesFoundException.cpp
** File description:
** header for NoScenesFoundException.c
*/

#include "polymorph/engine/debug/exception/core/NoScenesFoundException.hpp"


polymorph::engine::debug::NoScenesFoundException::NoScenesFoundException(Logger::severity level)
        : CoreException("No scenes found in the project", level) {}
