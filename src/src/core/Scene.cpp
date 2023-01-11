/*
** EPITECH PROJECT, 2020
** Scene.cpp
** File description:
** header for Scene.c
*/

#include <utility>

#include "polymorph/engine/core/Scene.hpp"
#include "polymorph/engine/core/Engine.hpp"
#include "polymorph/engine/config/XmlScene.hpp"
#include "polymorph/engine/types/uuid.hpp"
#include "polymorph/engine/core/entity/Entity.hpp"
#include "polymorph/engine/core/component/TransformComponent.hpp"
#include "polymorph/engine/time/Timer.hpp"

polymorph::engine::Scene::Scene(std::shared_ptr<myxmlpp::Node> &data, polymorph::engine::Engine &game)
        : _game(game)
{
    _config_data = std::make_shared<polymorph::engine::config::XmlScene>(data, game);

    id = _config_data->getId();
    name = _config_data->getName();
}

polymorph::engine::Scene::Scene(std::string sceneName, polymorph::engine::Engine &game)
        : _game(game), name(std::move(sceneName)), id(polymorph::engine::uuid::uuid())
{}

void polymorph::engine::Scene::update()
{
    _callMethodOnTopEntities([](std::shared_ptr<polymorph::engine::Entity> &e) {
        e->update();
    }, true);
}

void polymorph::engine::Scene::lateUpdate()
{
    _callMethodOnTopEntities([](std::shared_ptr<polymorph::engine::Entity> &e) {
        e->lateUpdate();
    }, true);
}

void polymorph::engine::Scene::start()
{
    _callMethodOnTopEntities([](std::shared_ptr<polymorph::engine::Entity> &e) {
        e->start();
    }, true);
}

void polymorph::engine::Scene::awake()
{
    _callMethodOnTopEntities([](std::shared_ptr<polymorph::engine::Entity> &e) {
        e->awake(true);
    }, false);
}

void polymorph::engine::Scene::build()
{
    for (auto &entity : _entities) {
        entity->transform = entity->getComponent<polymorph::engine::TransformComponent>();
        if (!entity->transform->parent())
            entity->build();
    }
}

void polymorph::engine::Scene::onSceneLoaded()
{
    auto sharedThis = shared_from_this();

    _callMethodOnTopEntities(
            [sharedThis](std::shared_ptr<polymorph::engine::Entity> &e) {
                e->onSceneLoaded(sharedThis);
            }, false);
}

void polymorph::engine::Scene::onSceneUnloaded()
{
    auto sharedThis = shared_from_this();

    _callMethodOnTopEntities(
            [sharedThis](std::shared_ptr<polymorph::engine::Entity> &e) {
                e->onSceneUnloaded(sharedThis);
            }, false);
}

void polymorph::engine::Scene::save(bool saveAllEntitiesFirst, std::string path)
{
    if (saveAllEntitiesFirst)
        for (auto &e : _entities)
            e->save(saveAllEntitiesFirst, path);
    _config_data->save(path, _entities);
}

void polymorph::engine::Scene::loadScene()
{
    auto entities = _config_data->getEntities();
    _destroyQueueList.clear();
    _entities.clear();

    for (auto &entity : *entities) {
        try {

        auto newEntity = std::make_shared<Entity>(entity, _game);
        newEntity->_createComponents();
        _entities.push_back(newEntity);
        } catch (debug::ExceptionLogger &e) {
            e.what();
            continue;
        }
    }
    build();
    auto &KeepOnLoad = _game.getSceneManager().getKeepedEntities();
    for (auto &e: KeepOnLoad)
        addEntity(e);
    KeepOnLoad.clear();
    onSceneLoaded();
    awake();
}

void polymorph::engine::Scene::unloadScene()
{
    onSceneUnloaded();
    _destroyQueueList.clear();
    _entities.clear();
}

void polymorph::engine::Scene::updateDestroyQueueList()
{
    std::map<std::shared_ptr<time::Timer>, Entity &> nmap;

    for (auto &destroyHolder : _destroyQueueList) {
        destroyHolder.first->tick();
        if (destroyHolder.first->timeIsUp()) {
            if (destroyHolder.second.transform->parent())
                destroyHolder.second.transform->parent()->removeChild(destroyHolder.second.transform);
            _eraseChildren(destroyHolder.second);
            _erase(destroyHolder.second);
        } else
            nmap.emplace(destroyHolder);
    }
    _destroyQueueList = nmap;
}

void polymorph::engine::Scene::updateAddQueueList()
{
    if (!_entitiesToAdd.empty()) {
        _entities.insert(_entities.end(), _entitiesToAdd.begin(), _entitiesToAdd.end());
        _entitiesToAdd.clear();
    }
}

std::vector<polymorph::engine::GameObject> polymorph::engine::Scene::getAll() const noexcept
{
    std::vector<GameObject> toRet;

    for (auto &e: _entities) {
        toRet.emplace_back(e);
    }
    return toRet;
}

polymorph::engine::GameObject polymorph::engine::Scene::find(const std::string &needle)
{
    auto it = std::find_if(_entities.begin(), _entities.end(), [&needle](const std::shared_ptr<polymorph::engine::Entity> &e) {
        return e->name == needle;
    });
    return it != _entities.end() ? GameObject(*it) : GameObject(nullptr);
}

std::vector<polymorph::engine::GameObject> polymorph::engine::Scene::findAll(const std::string &name)
{
    std::vector<GameObject> toRet;

    for (auto &e: _entities) {
        toRet.emplace_back(e);
    }
    return toRet;
}

polymorph::engine::GameObject polymorph::engine::Scene::findByTag(const std::string &tag)
{
    auto it = std::find_if(_entities.begin(), _entities.end(), [&tag](auto &e) {
        return e->hasTag(tag);
    });
    return it != _entities.end() ? GameObject(*it) : GameObject(nullptr);
}

std::vector<polymorph::engine::GameObject> polymorph::engine::Scene::findAllByTag(const std::string &tag)
{
    std::vector<GameObject> toRet;

    for (auto &e: _entities) {
        if (e->hasTag(tag))
            toRet.emplace_back(e);
    }
    return toRet;
}

polymorph::engine::GameObject polymorph::engine::Scene::findById(const std::string &id)
{
    auto it = findItById(id);
    return it != _entities.end() ? GameObject(*it) : GameObject(nullptr);
}

polymorph::engine::EntityIterator polymorph::engine::Scene::findItById(const std::string &id)
{
    return std::find_if(_entities.begin(), _entities.end(), [&id](auto &e) {
        return e->getId() == id;
    });
}

void polymorph::engine::Scene::addEntity(const std::shared_ptr<Entity> &entity)
{
    _entities.push_back(entity);
}

void polymorph::engine::Scene::addEntityToAddQueue(const std::shared_ptr<Entity> &entity)
{
    _entitiesToAdd.push_back(entity);
}

void polymorph::engine::Scene::addEntityAtIdx(const std::shared_ptr<Entity> &entity, std::size_t idx)
{
    _entities.insert(_entities.begin() + static_cast<int>(idx), entity);
}

void polymorph::engine::Scene::destroy(polymorph::engine::Entity &entity)
{
    destroy(entity, 0);
}

void polymorph::engine::Scene::destroy(polymorph::engine::Entity &entity, float delayInSeconds)
{
    auto e = std::find_if(_destroyQueueList.begin(), _destroyQueueList.end(),
                          [&entity](std::pair<std::shared_ptr<time::Timer>, Entity&> p) {
                              return p.second == entity;
                          }
    );
    if (e == _destroyQueueList.end()) {
        entity.setActive(false);
        _destroyQueueList.emplace(std::make_shared<time::Timer>(_game, delayInSeconds), entity);
    }
}

std::shared_ptr<polymorph::engine::Entity> polymorph::engine::Scene::pop(polymorph::engine::EntityIterator it)
{
    auto entity = *it;

    _entities.erase(it);
    return entity;
}

std::size_t polymorph::engine::Scene::countParents()
{
    std::size_t toRet = 0;

    for (auto &e : _entities) {
        if (!(e->transform->parent()))
            ++toRet;
    }
    return toRet;
}

void polymorph::engine::Scene::_erase(polymorph::engine::Entity &entity)
{
    auto idToErase = entity.getId();
    _erase(idToErase);
}

void polymorph::engine::Scene::_erase(std::string &id)
{
    std::erase_if(_entities, [&id](const std::shared_ptr<Entity> &e) {
        return e->getId() == id;
    });
}

void polymorph::engine::Scene::_eraseChildren(polymorph::engine::Entity &entity)
{
    for (auto &child: **entity.transform) {
        _eraseChildren(**child->gameObject);
        _erase(**child->gameObject);
    }
}

void polymorph::engine::Scene::_callMethodOnTopEntities(
        std::function<void(std::shared_ptr<Entity> &)> method,
        bool shouldExitOnSceneLoading)
{
    for (auto &e: _entities) {
        if (!e->transform->parent())
            method(e);
        if (shouldExitOnSceneLoading && (_game.isExiting() || _game.getSceneManager().isSceneUnloaded()))
            return;
    }
}
