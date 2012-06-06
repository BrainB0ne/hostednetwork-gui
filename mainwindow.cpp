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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutdialog.h"

#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_bTrayWarningShowed = false;

    createActions();
    createTrayIcon();
    setIcon();

    // validator to allow only ASCII characters
    QRegExp passphraseRegExp("^[\\x00-\\x7F]{8,63}$");
    QValidator *passphraseValidator = new QRegExpValidator(passphraseRegExp, this);
    ui->passphraseLineEdit->setValidator(passphraseValidator);

    ui->passphraseLineEdit->setFocus();
    statusBar()->hide();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    if(trayIcon)
    {
        trayIcon->show();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon && trayIcon->isVisible())
    {
        if(!m_bTrayWarningShowed)
        {
            QMessageBox::information(this, tr("WLAN Hosted Network Manager"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));
            m_bTrayWarningShowed = true;
        }

        hide();
        event->ignore();
    }
}

void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("E&xit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

void MainWindow::setIcon()
{
    QIcon icon = QIcon(":/images/wifi.png");
    trayIcon->setIcon(icon);
    setWindowIcon(icon);
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            showNormal();
            break;
        case QSystemTrayIcon::MiddleClick:
            break;
        default:
            ;
    }
}

bool MainWindow::runCommand(const QString& program, const QStringList& args)
{
    QProcess netsh;
    netsh.start(program, args);
    if (!netsh.waitForStarted())
        return false;

    netsh.closeWriteChannel();

    if (!netsh.waitForFinished())
        return false;

    QByteArray result = netsh.readAll();
    QString strResult = result.data();

    ui->logTextEdit->appendPlainText(strResult);

    // a little bit dirty, but it does the job :-)
    if(strResult.contains("The hosted network couldn't be started."))
    {
        ui->actionStart->setEnabled(true);
        ui->passphraseLineEdit->setEnabled(true);
        ui->ssidLineEdit->setEnabled(true);
    }
    else if(strResult.contains("The hosted network started."))
    {
        ui->actionStart->setEnabled(false);
        ui->passphraseLineEdit->setEnabled(false);
        ui->ssidLineEdit->setEnabled(false);
    }
    else if(strResult.contains("The hosted network stopped."))
    {
        ui->actionStart->setEnabled(true);
        ui->passphraseLineEdit->setEnabled(true);
        ui->ssidLineEdit->setEnabled(true);
    }

    return true;
}

void MainWindow::on_actionStart_triggered()
{
    ui->ssidLineEdit->setText(ui->ssidLineEdit->text().trimmed());

    if(ui->ssidLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Can't start WLAN Hosted Network.\nPlease fill in the SSID field.");
        return;
    }

    if(ui->passphraseLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Can't start WLAN Hosted Network.\nPlease fill in the Passphrase field.");
        return;
    }

    if((ui->passphraseLineEdit->text().length() < 8) || (ui->passphraseLineEdit->text().length() > 63))
    {
        QMessageBox::warning(this, "Warning", "Can't start WLAN Hosted Network.\nPlease fill in the Passphrase field correctly (8-63 ASCII characters).");
        return;
    }

    ui->logTextEdit->appendPlainText("> Starting WLAN Hosted Network ...");

    QStringList argsSet;
    argsSet << "wlan" << "set" << "hostednetwork" << "mode=allow";
    argsSet << QString("ssid=%1").arg(ui->ssidLineEdit->text());
    argsSet << QString("key=%1").arg(ui->passphraseLineEdit->text());

    bool ok = runCommand("netsh", argsSet);

    if(!ok)
    {
        QMessageBox::critical(this, "Error", "Netsh command failed to execute!");
    }

    QStringList argsStart;
    argsStart << "wlan" << "start" << "hostednetwork";

    ok = runCommand("netsh", argsStart);

    if(!ok)
    {
        QMessageBox::critical(this, "Error", "Netsh command failed to execute!");
    }
}

void MainWindow::on_actionStop_triggered()
{
    ui->logTextEdit->appendPlainText("> Stopping WLAN Hosted Network ...");

    QStringList args;
    args << "wlan" << "stop" << "hostednetwork";

    bool ok = runCommand("netsh", args);

    if(!ok)
    {
        QMessageBox::critical(this, "Error", "Netsh command failed to execute!");
    }

}

void MainWindow::on_actionShow_triggered()
{
    ui->logTextEdit->appendPlainText("> Show WLAN Hosted Network ...");

    QStringList args;
    args << "wlan" << "show" << "hostednetwork";

    bool ok = runCommand("netsh", args);

    if(!ok)
    {
        QMessageBox::critical(this, "Error", "Netsh command failed to execute!");
    }

}

void MainWindow::on_showPassphraseCheckBox_toggled(bool checked)
{
    if(checked)
    {
        ui->passphraseLineEdit->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->passphraseLineEdit->setEchoMode(QLineEdit::Password);
    }
}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionMinimizeToTray_triggered()
{
    hide();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog* aboutDlg = new AboutDialog(this);
    if(aboutDlg)
    {
        aboutDlg->exec();

        delete aboutDlg;
        aboutDlg = 0;
    }
}
