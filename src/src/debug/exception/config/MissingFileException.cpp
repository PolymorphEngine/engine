/*
** EPITECH PROJECT, 2020
** MissingFileException.cpp
** File description:
** header for MissingFileException.c
*/

#include "polymorph/engine/debug/exception/config/MissingFileException.hpp"

polymorph::engine::debug::MissingFileException::MissingFileException(
        std::string file, Logger::severity level)
        : ConfigurationException("file not found at path '"+file+"'", level)
{

}
