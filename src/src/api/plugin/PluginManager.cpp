/*
** EPITECH PROJECT, 2020
** PluginManager.cpp
** File description:
** header for PluginManager.c
*/

#include "polymorph/api/plugin/PluginManager.hpp"
#include "polymorph/debug/exception/plugin/PluginDisabledException.hpp"
#include "polymorph/debug/exception/plugin/PluginNotFoundException.hpp"


namespace polymorph::engine::api
{
    api::PluginManager::PluginManager(Engine &game) : _game(game)
    {

    }

    void api::PluginManager::loadPlugins(const std::string &pluginsPath,
                                         config::XmlNode &list,
                                         Engine &game)
    {
        _pluginsOrder = _game.getPluginExecOrder();
        for (auto &node : list) {
            auto name = node->findAttribute("name")->getValue();
            _game.getAssetManager().addPath(pluginsPath + "/" + name + "/Assets/");
        }
        for (auto &node : list) {
            auto name = node->findAttribute("name")->getValue();
            try {
                auto plugin = _loadPlugin(node, pluginsPath + name, game, name);
                _plugins.push_back(plugin);
            } catch (debug::ExceptionLogger &e) {
                e.what();
            }
        }
    }

    AssetManager &api::PluginManager::getAssetManager()
    {
        return _game.getAssetManager();
    }

    std::shared_ptr<AComponent>
    api::PluginManager::tryCreateComponent(std::string &type, GameObject entity,
                                           std::shared_ptr<myxmlpp::Node> node)
    {
        for (auto &plugin : _plugins) {
            if (plugin->hasObject(type))
            {
                if (!plugin->isEnabled())
                    throw debug::PluginDisabledException(plugin->getPluginName(), type);
                return plugin->createComponent<AComponent>(type, entity, node);
            }
        }
        throw debug::PluginNotFoundException(type);
    }

    std::shared_ptr <ASerializableObject>
    api::PluginManager::tryCreateComponentObject(std::string &type,
                                                 std::shared_ptr <myxmlpp::Node> &data,
                                                 safe_ptr <AComponent> component)
    {
        for (auto &plugin : _plugins) {
            if (plugin->hasObject(type))
            {
                if (!plugin->isEnabled())
                    throw debug::PluginDisabledException(plugin->getPluginName(), type);
                return plugin->createSerializableObject<ASerializableObject>(type, component, data);
            }
        }
        throw debug::PluginNotFoundException(type);
    }

    std::shared_ptr <ASerializableObject>
    api::PluginManager::tryCreateConfigObject(std::string &type,
                                              std::shared_ptr <myxmlpp::Node> &data,
                                              safe_ptr<APluginConfig> component)
    {
        for (auto &plugin : _plugins) {
            if (plugin->hasObject(type))
            {
                if (!plugin->isEnabled())
                    throw debug::PluginDisabledException(plugin->getPluginName(), type);
                return plugin->createConfigObject<ASerializableObject>(type, component, data);
            }
        }
        throw debug::PluginNotFoundException(type);
    }

    std::shared_ptr<ASerializableObject>
    api::PluginManager::tryCreateEmptyObject(std::string &type)
    {
        for (auto &plugin : _plugins) {
            if (plugin->hasObject(type))
            {
                if (!plugin->isEnabled())
                    throw debug::PluginDisabledException(plugin->getPluginName(), type);
                return plugin->createEmptySharedObject<ASerializableObject>(type, *this);
            }
        }
        throw debug::PluginNotFoundException(type);
    }

    std::vector <config::XmlComponent>
    api::PluginManager::getTemplates()
    {
        std::vector<config::XmlComponent> templates;

        for (auto &plugin : _plugins) {
            if (plugin->isEnabled())
            {
                auto tmp = plugin->getComponentTemplates();
                templates.insert(templates.end(), tmp.begin(), tmp.end());
            }
        }
        return templates;
    }

    GameObject api::PluginManager::getPrefab(const std::string &id)
    {
        for (auto &plugin : _plugins) {
            if (plugin->isEnabled() && plugin->hasPrefab(id))
            {
                auto e = plugin->getPrefabConf(id);
                _prefabs.emplace_back(e);
                return GameObject(_prefabs.back());
            }
        }
        return GameObject(nullptr);
    }

    void api::PluginManager::startingScripts()
    {
        auto c = _game.getSceneManager().getCurrentScene();
        for (auto &plugin : _pluginsOrder) {
            auto res = std::find_if(_plugins.begin(), _plugins.end(), [&plugin](const auto &p) {
                return p->getPluginName() == plugin;});
            if (res != _plugins.end() && (*res)->isEnabled())
                (*res)->startScripts(c);
            if (_game.isExiting())
                return;
        }

        for (auto &plugin : _plugins) {
            if (!_isPluginPrioritary(plugin->getPluginName()) && plugin->isEnabled())
                plugin->startScripts(c);
            if (_game.isExiting())
                return;
        }
    }

    void api::PluginManager::preProcessing()
    {
        auto c = _game.getSceneManager().getCurrentScene();
        for (auto &plugin : _pluginsOrder) {
            auto res = std::find_if(_plugins.begin(), _plugins.end(), [&plugin](const auto &p) {
                return p->getPluginName() == plugin;});
            if (res != _plugins.end() && (*res)->isEnabled())
                (*res)->preUpdateInternalSystems(c);
            if (_game.isExiting() || _game.getSceneManager().isSceneUnloaded())
                return;
        }

        for (auto &plugin : _plugins) {
            if (!_isPluginPrioritary(plugin->getPluginName()) && plugin->isEnabled())
                plugin->preUpdateInternalSystems(c);
            if (_game.isExiting() || _game.getSceneManager().isSceneUnloaded())
                return;
        }
    }

    void api::PluginManager::lateUpdate()
    {
        auto c = _game.getSceneManager().getCurrentScene();
        for (auto &plugin : _pluginsOrder) {
            auto res = std::find_if(_plugins.begin(), _plugins.end(), [&plugin](const auto &p) {
                return p->getPluginName() == plugin;});
            if (res != _plugins.end() && (*res)->isEnabled())
                (*res)->updateInternalSystems(c);
            if (_game.isExiting() || _game.getSceneManager().isSceneUnloaded())
                return;
        }

        for (auto &plugin : _plugins) {
            if (!_isPluginPrioritary(plugin->getPluginName()) && plugin->isEnabled())
                plugin->updateInternalSystems(c);
            if (_game.isExiting() || _game.getSceneManager().isSceneUnloaded())
                return;
        }
    }

    void api::PluginManager::postProcessing()
    {
        auto c = _game.getSceneManager().getCurrentScene();
        for (auto &plugin : _pluginsOrder) {
            auto res = std::find_if(_plugins.begin(), _plugins.end(), [&plugin](const auto &p) {
                return p->getPluginName() == plugin;});
            if (res != _plugins.end() && (*res)->isEnabled())
                (*res)->postUpdateInternalSystems(c);
            if (_game.isExiting() || _game.getSceneManager().isSceneUnloaded())
                return;
        }

        for (auto &plugin : _plugins) {
            if (!_isPluginPrioritary(plugin->getPluginName()) && plugin->isEnabled())
                plugin->postUpdateInternalSystems(c);
            if (_game.isExiting() || _game.getSceneManager().isSceneUnloaded())
                return;
        }
    }

    void api::PluginManager::endingScripts()
    {
        auto c = _game.getSceneManager().getCurrentScene();
        for (auto &plugin : _pluginsOrder) {
            auto res = std::find_if(_plugins.begin(), _plugins.end(), [&plugin](const auto &p) {
                return p->getPluginName() == plugin;});
            if (res != _plugins.end() && (*res)->isEnabled())
                (*res)->endScripts(c);
            if (_game.isExiting() || _game.getSceneManager().isSceneUnloaded())
                return;
        }

        for (auto &plugin : _plugins) {
            if (!_isPluginPrioritary(plugin->getPluginName()) && plugin->isEnabled())
                plugin->endScripts(c);
            if (_game.isExiting() || _game.getSceneManager().isSceneUnloaded())
                return;
        }
    }

    bool api::PluginManager::_isPluginPrioritary(
            const std::string &pluginName)
    {
        for (auto &plugin : _pluginsOrder)
            if (plugin == pluginName)
                return true;
        return false;
    }

    std::shared_ptr <APlugin> api::PluginManager::_loadPlugin(
            std::shared_ptr <config::XmlNode> node,
            const std::string &pluginPath, Engine &game,
            const std::string &name)
    {
        _pluginsLoaders.emplace_back();
        _pluginsPath.emplace_back(pluginPath);
#ifdef _WIN32
        _pluginsLoaders.back().loadHandler(pluginPath +"/"+ name + ".dll");
#else
        _pluginsLoaders.back().loadHandler(pluginPath +"/"+ name + ".so");
#endif
        auto loader = _pluginsLoaders.back().loadSymbol<Symbols::createPluginDEF>(Symbols::createPlugin);
        return std::shared_ptr<APlugin>(loader(*node, game, pluginPath));
    }
} // api