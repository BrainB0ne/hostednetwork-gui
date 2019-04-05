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

#include <QApplication>
#include <QCommandLineParser>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QApplication::setApplicationName("WLAN Hosted Network Manager");
    QApplication::setApplicationVersion("0.2.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("WLAN Hosted Network Manager");
    parser.addHelpOption();
    parser.addVersionOption();

    // A boolean option with a single name (-a)
    QCommandLineOption autoStartOption("a", QCoreApplication::translate("main", "Automatically start hosted network"));
    parser.addOption(autoStartOption);

    // Process the actual command line arguments given by the user
    parser.process(app);

    bool autoStart = parser.isSet(autoStartOption);

    MainWindow w;

    w.initialize(autoStart);
    w.show();
    
    return app.exec();
}
