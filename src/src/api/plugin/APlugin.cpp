/*
** EPITECH PROJECT, 2020
** APlugin.cpp
** File description:
** APlugin.cpp
*/

#include "polymorph/engine/api/plugin/APlugin.hpp"
#include "polymorph/engine/api/plugin/APluginConfig.hpp"
#include "polymorph/engine/core/Engine.hpp"
#include "polymorph/engine/config/XmlComponent.hpp"
#include "polymorph/engine/config/XmlEntity.hpp"

#include "polymorph/engine/debug/exception/plugin/CorruptedPluginException.hpp"

namespace polymorph::engine::api
{

    APlugin::APlugin(config::XmlNode &data, Engine &game,
                     std::string PluginsPath) : _data(data), _game(game),
                                                pluginManager(game.getPluginManager()),
                                                assetManager(game.getAssetManager()), _pluginsPath(std::move(PluginsPath))
    {
        try {
            _packageName = _data.findAttribute("name")->getValue();
            _isEnabled = _data.findAttribute("enabled")->getValueBool();
        } catch (myxmlpp::AttributeNotFoundException &e) {
            throw debug::CorruptedPluginException((_packageName.empty()) ? _pluginsPath : _packageName);
        }
        _loadConfig();
        if (!_isEnabled)
            return;
        _loadTemplates();
        _loadPrefabs();
    }

    bool APlugin::isEnabled() const
    {
        return _isEnabled;
    }

    bool APlugin::hasComponent(std::string &type)
    {
        return _factory->hasComponent(type);
    }

    bool APlugin::hasObject(std::string &type)
    {
        return _objectFactory->hasObject(type);
    }

    bool APlugin::hasPrefab(const std::string &id)
    {
        return (std::find_if(_prefabs.begin(), _prefabs.end(),
        [&id](const std::shared_ptr<config::XmlEntity> &prefab) {
            return (prefab->getId() == id);
        }) != _prefabs.end());
    }

    std::shared_ptr<config::XmlEntity> &
    APlugin::getPrefabConf(const std::string &id)
    {
        return *std::find_if(_prefabs.begin(), _prefabs.end(), [id](const std::shared_ptr<config::XmlEntity> &prefab) {
            return prefab->getId() == id;
        });
    }

    std::vector<std::shared_ptr<myxmlpp::Node>> &APlugin::getComponentTemplates()
    {
        return _templates;
    }

    void APlugin::preUpdateInternalSystems(std::shared_ptr<Scene> &scene)
    {

    }

    void APlugin::updateInternalSystems(std::shared_ptr<Scene> &scene)
    {

    }

    void APlugin::postUpdateInternalSystems(std::shared_ptr<Scene> &scene)
    {

    }

    void APlugin::startScripts(std::shared_ptr<Scene> &scene)
    {

    }

    void APlugin::endScripts(std::shared_ptr<Scene> &scene)
    {

    }

    void APlugin::_loadPrefabs()
    {
        auto prefabs = _doc->getRoot()->findChild("Prefabs");

        for (auto &t: *prefabs) {
            _prefabs.emplace_back(std::make_shared<config::XmlEntity>(t, _game.getLogger(), _game));
        }
    }

    void APlugin::_loadTemplates()
    {
        auto prefabs = _doc->getRoot()->findChild("Templates");

        for (auto &t: *prefabs) {
            std::shared_ptr<myxmlpp::Doc> tmp;
            try {
                tmp = std::make_shared<myxmlpp::Doc>(assetManager.tryResolve(t->findAttribute("path")->getValue()));
            } catch (const myxmlpp::Exception &e) {
                debug::PluginException(_packageName, "Failed to load template at path: " + t->findAttribute("path")->getValue()).what();
                continue;
            } catch (const debug::CoreException &e) {
                e.what();
                debug::PluginException(_packageName, "Failed to load template at path: " + t->findAttribute("path")->getValue()).what();
                continue;
            }
            _templates.push_back(tmp->getRoot());
        }
    }

    void APlugin::_loadConfig()
    {
        try {
            _doc = std::make_shared<myxmlpp::Doc>(_pluginsPath + "/" + _packageName + ".pcf.plugin");
        } catch (myxmlpp::NoFileException &e) {
            throw debug::CorruptedPluginException(_packageName);
        } catch (myxmlpp::FileException &e) {
            throw debug::CorruptedPluginException(_packageName);
        } catch (myxmlpp::ParsingException &e) {
            throw debug::CorruptedPluginException(_packageName);
        }
    }

    std::string APlugin::getPluginName()
    {
        return _packageName;
    }

    void APlugin::build()
    {
        createConfig(_configs);
        _factory = createComponentFactory();
        _objectFactory = createSerializableObjectFactory();
        _factory->buildFactory();
        _objectFactory->buildFactory();
    }

    safe_ptr<APluginConfig> APlugin::getConfig(const std::string &type)
    {
        for (auto &config : _configs) {
            if (config->getType() == type)
                return safe_ptr<APluginConfig>(config);
        }
        return safe_ptr<APluginConfig>(nullptr);
    }
} // api