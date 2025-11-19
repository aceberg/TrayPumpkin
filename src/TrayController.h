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
    void updateIcon();
    void runStart();
    void runStop();

private slots:
    void handleLeftClick(QSystemTrayIcon::ActivationReason reason);
    void quitApp();

private:
    AppConfig m_config;

    QSystemTrayIcon *m_tray = nullptr;
    QMenu *m_menu = nullptr;

    QAction *m_startAction = nullptr;
    QAction *m_stopAction = nullptr;
    QAction *m_quitAction = nullptr;

    bool m_running = false;
};
