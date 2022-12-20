/*
** EPITECH PROJECT, 2020
** CorruptedFileException.cpp
** File description:
** header for CorruptedFileException.c
*/

#include "polymorph/engine/debug/exception/config/CorruptedFileException.hpp"

polymorph::engine::debug::CorruptedFileException::CorruptedFileException(
        std::string file, Logger::severity level)
        : ConfigurationException("'"+file + "' is corrupted.", level)
{

}
