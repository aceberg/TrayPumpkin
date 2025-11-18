// AppConfig.h
#pragma once
#include <QString>

class AppConfig {
public:
    AppConfig(const QString &path);
    bool isValid() const;

    QString appName() const { return m_appName; }
    QString startCmd() const { return m_startCmd; }
    QString stopCmd() const  { return m_stopCmd; }
    QString iconNormal() const { return m_iconNormal; }
    QString iconRunning() const  { return m_iconRunning; }

private:
    QString m_path;
    QString m_appName;
    QString m_startCmd;
    QString m_stopCmd;
    QString m_iconNormal;
    QString m_iconRunning;
    bool m_valid = false;
};
