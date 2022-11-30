/*
** ${PROJECT}, 2022
** AComponent.cpp by 0xMemoryGrinder
** File description:
** AComponent.cpp
*/


#include "polymorph/core/component/AComponent.hpp"
#include "polymorph/core/entity/Entity.hpp"

polymorph::engine::AComponent::AComponent(std::shared_ptr<myxmlpp::Node> data, polymorph::engine::GameObject gameObject)
        : gameObject(gameObject), Plugin(gameObject->Plugin),
          Scene(gameObject->Scene), Asset(gameObject->Asset), Factory(gameObject->Factory),
          Debug(gameObject->Debug), time(gameObject->time), Game(gameObject->Game)
{
    
}

void polymorph::engine::AComponent::update() {}

void polymorph::engine::AComponent::onAwake() {}

void polymorph::engine::AComponent::start() {}

void polymorph::engine::AComponent::setAsStarted() noexcept
{
    _started = true;
}

void polymorph::engine::AComponent::setAsAwoken() noexcept
{
    _awoken = true;
}

bool polymorph::engine::AComponent::isAwoken() const noexcept
{
    return _awoken;
}

bool polymorph::engine::AComponent::isStarted() const noexcept
{
    return _started;
}

std::string polymorph::engine::AComponent::getType() const noexcept
{
    return _type;
}


