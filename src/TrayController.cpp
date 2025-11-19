#include "TrayController.h"
#include <QAction>
#include <QApplication>
#include <QProcess>
#include <QDebug>

TrayController::TrayController(const AppConfig &config, QObject *parent)
    : QObject(parent), m_config(config)
{
    m_tray = new QSystemTrayIcon(this);
    m_menu = new QMenu();

    setupMenu();
    updateIcon();

    // Tooltip
    if (!m_config.tooltip().isEmpty())
        m_tray->setToolTip(m_config.tooltip());

    // Handle left click toggle Start/Stop
    connect(m_tray, &QSystemTrayIcon::activated,
            this, &TrayController::handleLeftClick);

    m_tray->setContextMenu(m_menu);
    m_tray->show();
}

//
// Build menu from YAML
//
void TrayController::setupMenu()
{
    // Top title
    if (!m_config.appName().isEmpty()) {
        QAction *title = m_menu->addAction(m_config.appName());
        // title->setEnabled(false);
        m_menu->addSeparator();
    }

    //
    // Dynamic YAML menu items
    //
    for (const MenuItem &item : m_config.menuItems()) {
        if (item.isSeparator) {
            m_menu->addSeparator();
            continue;
        }

        QAction *action = m_menu->addAction(item.name);

        connect(action, &QAction::triggered, this, [item]() {
            if (!item.command.isEmpty())
                QProcess::startDetached("/bin/sh", {"-c", item.command});
        });
    }

    if (!m_config.menuItems().isEmpty())
        m_menu->addSeparator();

    //
    // Start/Stop actions
    //
    m_startAction = m_menu->addAction("Start");
    m_stopAction  = m_menu->addAction("Stop");
    m_stopAction->setEnabled(false);

    connect(m_startAction, &QAction::triggered, this, &TrayController::runStart);
    connect(m_stopAction,  &QAction::triggered, this, &TrayController::runStop);

    m_menu->addSeparator();

    //
    // Quit
    //
    m_quitAction = m_menu->addAction("Quit");
    connect(m_quitAction, &QAction::triggered, this, &TrayController::quitApp);
}

//
// Update icon based on running state
//
void TrayController::updateIcon()
{
    QString iconPath = m_running ? m_config.iconRunning()
                                 : m_config.iconNormal();

    if (!iconPath.isEmpty())
        m_tray->setIcon(QIcon(iconPath));
}

//
// Run start command
//
void TrayController::runStart()
{
    m_running = true;

    if (!m_config.startCmd().isEmpty())
        QProcess::startDetached("/bin/sh", {"-c", m_config.startCmd()});

    m_startAction->setEnabled(false);
    m_stopAction->setEnabled(true);

    updateIcon();
}

//
// Run stop command
//
void TrayController::runStop()
{
    m_running = false;

    if (!m_config.stopCmd().isEmpty())
        QProcess::startDetached("/bin/sh", {"-c", m_config.stopCmd()});

    m_startAction->setEnabled(true);
    m_stopAction->setEnabled(false);

    updateIcon();
}

//
// Toggle on left-click
//
void TrayController::handleLeftClick(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) { // left-click
        if (m_running)
            runStop();
        else
            runStart();
    }
}

//
// Quit: first run Stop, then exit
//
void TrayController::quitApp()
{
    if (m_running)
        runStop();

    qApp->quit();
}
