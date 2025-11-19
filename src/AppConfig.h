#pragma once
#include <QString>
#include <QList>

struct MenuItem {
    bool isSeparator = false;
    QString name;
    QString command;
};

class AppConfig
{
public:
    explicit AppConfig(const QString &path);

    bool isValid() const;

    QString appName() const { return m_appName; }
    QString tooltip() const { return m_tooltip; }

    QString startCmd() const { return m_startCmd; }
    QString stopCmd() const { return m_stopCmd; }

    QString iconNormal() const { return m_iconNormal; }
    QString iconRunning() const { return m_iconRunning; }

    const QList<MenuItem>& menuItems() const { return m_menuItems; }

private:
    bool m_valid = false;
    QString m_path;

    QString m_appName;
    QString m_tooltip;

    QString m_startCmd;
    QString m_stopCmd;

    QString m_iconNormal;
    QString m_iconRunning;

    QList<MenuItem> m_menuItems;
};
