#include "AppConfig.h"
#include <QFile>
#include <QDebug>
#include <yaml-cpp/yaml.h>

AppConfig::AppConfig(const QString &path)
    : m_path(path)
{
    if (!QFile::exists(path)) {
        qWarning() << "Config file does not exist:" << path;
        m_valid = false;
        return;
    }

    YAML::Node root;
    try {
        root = YAML::LoadFile(path.toStdString());
    } catch (const std::exception &e) {
        qWarning() << "YAML parse error:" << e.what();
        m_valid = false;
        return;
    }

    m_valid = true;

    //
    // App section
    //
    if (root["app"]) {
        if (root["app"]["name"])
            m_appName = QString::fromStdString(root["app"]["name"].as<std::string>());

        if (root["app"]["tooltip"])
            m_tooltip = QString::fromStdString(root["app"]["tooltip"].as<std::string>());
    }

    //
    // Icons section
    //
    if (root["icons"]) {
        if (root["icons"]["normal"])
            m_iconNormal = QString::fromStdString(root["icons"]["normal"].as<std::string>());

        if (root["icons"]["running"])
            m_iconRunning = QString::fromStdString(root["icons"]["running"].as<std::string>());
    }

    //
    // Commands section
    //
    if (root["commands"]) {
        if (root["commands"]["start"])
            m_startCmd = QString::fromStdString(root["commands"]["start"].as<std::string>());

        if (root["commands"]["stop"])
            m_stopCmd = QString::fromStdString(root["commands"]["stop"].as<std::string>());
    }

    //
    // Menu
    //
    if (root["menu"] && root["menu"].IsSequence()) {
        for (const auto &item : root["menu"]) {

            // separator
            if (item["separator"] && item["separator"].as<bool>()) {
                MenuItem sep;
                sep.isSeparator = true;
                m_menuItems.append(sep);
                continue;
            }

            // menu entry with name + cmd
            if (item["name"] && item["cmd"]) {
                MenuItem mi;
                mi.isSeparator = false;
                mi.name = QString::fromStdString(item["name"].as<std::string>());
                mi.command = QString::fromStdString(item["cmd"].as<std::string>());
                m_menuItems.append(mi);
            }
        }
    }
}

bool AppConfig::isValid() const
{
    return m_valid;
}
