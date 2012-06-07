/*
 * WLAN Hosted Network Manager
 * Copyleft 2012
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

    bool runCommand(const QString& program, const QStringList& args);
    bool runAndParseShowHostedNetworkCommand();

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
    void on_actionExit_triggered();
    void on_actionMinimizeToTray_triggered();
    void on_actionAbout_triggered();
    void on_showPassphraseCheckBox_toggled(bool checked);
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
