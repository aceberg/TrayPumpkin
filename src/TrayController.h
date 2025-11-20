#pragma once
#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include "AppConfig.h"

class TrayController : public QObject
{
    Q_OBJECT

public:
    explicit TrayController(const AppConfig &config, QObject *parent = nullptr);

private:
    void setupMenu();
    void runMenuItem(const MenuItem &item);

private slots:
    void handleLeftClick(QSystemTrayIcon::ActivationReason reason);
    void quitApp();

private:
    AppConfig m_config;

    QSystemTrayIcon *m_tray = nullptr;
    QMenu *m_menu = nullptr;

    QAction *m_quitAction = nullptr;

    bool m_running = false;
};
