/*
** EPITECH PROJECT, 2020
** SceneNotFoundException.cpp
** File description:
** header for SceneNotFoundException.c
*/

#include "polymorph/engine/debug/exception/core/SceneNotFoundException.hpp"

polymorph::engine::debug::SceneNotFoundException::SceneNotFoundException(std::string name, Logger::severity level)
        : CoreException("Scene: " + name + " not found", level) {}
