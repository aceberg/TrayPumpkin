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

    runMenuItem(m_config.mainApp());

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
    if (!m_config.mainApp().name.isEmpty()) {
        QAction *title = m_menu->addAction(m_config.mainApp().name);
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

        connect(action, &QAction::triggered, this, [this, item]() {
            runMenuItem(item);
        });
    }

    if (!m_config.menuItems().isEmpty())
        m_menu->addSeparator();

    //
    // Quit
    //
    m_quitAction = m_menu->addAction("Quit");
    connect(m_quitAction, &QAction::triggered, this, &TrayController::quitApp);
}

void TrayController::runMenuItem(const MenuItem &item)
{
    if (item.isSeparator)
        return;

    if (!item.command.isEmpty()) {
        QProcess::startDetached("/bin/sh", {"-c", item.command});
    }

    if (!item.icon.isEmpty())
        m_tray->setIcon(QIcon(item.icon));

    if (!item.tooltip.isEmpty())
        m_tray->setToolTip(item.tooltip);
}

//
// Toggle on left-click
//
void TrayController::handleLeftClick(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) { // left-click
        if (m_running && !m_config.leftToggle().command.isEmpty()) {
            m_running = false;
            runMenuItem(m_config.leftToggle());
        } else {
            m_running = true;
            runMenuItem(m_config.leftClick());
        }
    }
}

//
// Quit: first run Stop, then exit
//
void TrayController::quitApp()
{
    runMenuItem(m_config.quitApp());

    qApp->quit();
}
