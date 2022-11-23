/*
** EPITECH PROJECT, 2020
** SceneNotFoundException.cpp
** File description:
** header for SceneNotFoundException.c
*/

#include "polymorph/debug/exception/core/SceneNotFoundException.hpp"

polymorph::engine::debug::SceneNotFoundException::SceneNotFoundException(std::string name, Logger::severity level)
        : ExceptionLogger("[SceneNotFoundException] Scene: " + name + " not found", level) {}
