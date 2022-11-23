/*
** EPITECH PROJECT, 2020
** ExceptionLogger.cpp
** File description:
** header for ExceptionLogger.c
*/

#include "polymorph/debug/exception/ExceptionLogger.hpp"

polymorph::engine::debug::ExceptionLogger::ExceptionLogger(std::string message,
polymorph::engine::debug::Logger::severity level)
{
    this->_message = message;
    this->_level = level;

}

const char *polymorph::engine::debug::ExceptionLogger::what() const noexcept
{
    Logger::Log(this->_message, this->_level);
    return this->_message.c_str();
}
