#pragma once
#include <QString>
#include <QList>
#include <yaml-cpp/yaml.h>

struct MenuItem {
    bool isSeparator = false;
    QString name;
    QString command;
    QString icon;
    QString tooltip;
};

class AppConfig
{
public:
    explicit AppConfig(const QString &path);

    bool isValid() const;

    MenuItem mainApp() const { return m_mainApp; }

    MenuItem leftClick() const { return m_leftClick; }
    MenuItem leftToggle() const { return m_leftToggle; }

    MenuItem quitApp() const { return m_quitApp; }

    const QList<MenuItem>& menuItems() const { return m_menuItems; }

private:
    bool m_valid = false;
    QString m_path;

    MenuItem m_mainApp;

    MenuItem m_leftClick;
    MenuItem m_leftToggle;

    MenuItem m_quitApp;

    QList<MenuItem> m_menuItems;

    MenuItem loadNamedItem(const YAML::Node &node);
};
