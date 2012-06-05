#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void createActions();
    void createTrayIcon();
    void setIcon();

private slots:
    void on_actionStart_triggered();
    void on_actionStop_triggered();
    void on_actionShow_triggered();
    void on_actionRefresh_triggered();
    void on_actionExit_triggered();
    void on_actionMinimizeToTray_triggered();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow *ui;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    bool m_bProcessRunning;
    bool m_bTrayWarningShowed;
};

#endif // MAINWINDOW_H
