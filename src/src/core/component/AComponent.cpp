/*
** ${PROJECT}, 2022
** AComponent.cpp by 0xMemoryGrinder
** File description:
** AComponent.cpp
*/


#include "polymorph/core/component/AComponent.hpp"

#include "polymorph/config/XmlComponent.hpp"
#include "polymorph/core/Scene.hpp"
#include "polymorph/api/AssetManager.hpp"

polymorph::engine::AComponent::AComponent(std::shared_ptr<myxmlpp::Node> data, polymorph::engine::GameObject gameObject)
        : gameObject(gameObject), Plugin(gameObject->Plugin),
          Scene(gameObject->Scene), Asset(gameObject->Resource),
          Debug(gameObject->Debug), time(gameObject->time), Game(gameObject->Game)
{
    _xmlConfig = std::make_shared<config::XmlComponent>(gameObject, data, Debug);
    
    _type = _xmlConfig->getType();
    enabled = _xmlConfig->getEnabled();
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

void polymorph::engine::AComponent::lateUpdate()
{

}

void polymorph::engine::AComponent::onSceneLoaded(
        std::shared_ptr<engine::Scene> scene)
{

}

void polymorph::engine::AComponent::onSceneUnloaded(
        std::shared_ptr<engine::Scene> scene)
{

}

std::shared_ptr<myxmlpp::Node> polymorph::engine::AComponent::getNode()
{
    return _xmlConfig->getNode();
}

std::shared_ptr<polymorph::engine::config::XmlComponent> polymorph::engine::AComponent::getConfig()
{
    return _xmlConfig;
}


