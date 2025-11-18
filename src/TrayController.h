// TrayController.h
#pragma once
#include <QObject>
#include <QIcon>

class AppConfig;
class KStatusNotifierItem;
class QMenu;

class TrayController : public QObject
{
    Q_OBJECT

public:
    TrayController(const AppConfig &config);

private:
    void start();
    void stop();
    void toggle();
    void runCommand(const QString &cmd);

    const AppConfig &m_config;
    KStatusNotifierItem *m_item = nullptr;
    QMenu *m_menu = nullptr;

    bool running = false;

    QIcon iconNormal;
    QIcon iconRunning;
};
