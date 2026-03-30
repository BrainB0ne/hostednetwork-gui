# AGENTS.md

This file provides guidelines for agentic coding agents working in this repository.

## Project Overview

Qt/C++ GUI application for managing Windows WLAN hosted networks (Virtual WiFi).
- **Language**: C++17
- **Framework**: Qt 5.15.2 (Qt5::Widgets, Qt5::Gui)
- **Platform**: Windows only (uses `netsh` commands)
- **License**: GPL v3

## Build Commands

### Primary Build (CMake)
```bash
# Configure
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build --config Release

# Test (currently no tests defined)
ctest -C Release --output-on-failure
```

### Legacy Build (qmake)
```bash
# Alternative build using qmake
qmake hostednetwork-gui.pro
nmake              # or: mingw32-make
```

### Qt Creator
Open `hostednetwork-gui.pro` or `CMakeLists.txt` directly in Qt Creator.

**Note**: This project has no unit tests currently. All testing is manual/integration.

## Code Style Guidelines

### File Headers
All source files must include the GPL v3 license header:
```cpp
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
```

### Include Order
```cpp
// 1. Own header (for .cpp files)
#include "thisfile.h"

// 2. Other local headers
#include "otherdialog.h"
#include "ui_thisfile.h"      // UI headers after local headers

// 3. Qt headers (alphabetical within groups)
#include <QApplication>
#include <QProcess>
#include <QTimer>
```

### Naming Conventions

**Classes**: PascalCase
```cpp
class MainWindow : public QMainWindow
class AboutDialog : public QDialog
```

**Member Variables**: `m_<type><Name>`
- Pointer: `m_p<Name>` (e.g., `m_pSettings`, `m_pLicenseDlg`)
- Boolean: `m_b<Name>` (e.g., `m_bProcessRunning`, `m_bTrayWarningShowed`)

**Methods/Functions**: camelCase
```cpp
void initialize();
void loadSettings();
bool runCommand(const QString& program, const QStringList& args);
```

**Qt Slots**: Follow Qt naming convention for auto-connect
```cpp
private slots:
    void on_actionStart_triggered();     // Auto-connected to UI action
    void on_showPassphraseCheckBox_toggled(bool checked);
    void slotLicenseButtonClicked();       // Manual slots use "slot" prefix
```

### Formatting
- **Indentation**: 4 spaces (no tabs)
- **Braces**: K&R style (same line)
- **Pointer/reference**: Left-aligned with type (`QString& args`, `int* ptr`)
- **Line length**: ~100-120 characters max

Example:
```cpp
void MainWindow::initialize()
{
    createActions();
    createTrayIcon();
    setIcon();

    if(trayIcon)
    {
        trayIcon->show();
    }
}
```

### Qt-Specific Patterns

**Memory Management**: Use Qt parent-child hierarchy
```cpp
// Good: Qt handles deletion via parent
QValidator *passphraseValidator = new QRegExpValidator(passphraseRegExp, this);

// Manual deletion in destructor for non-Qt-parented pointers
if(m_pSettings)
{
    delete m_pSettings;
    m_pSettings = 0;    // Null after delete
}
```

**Signal/Slot Connections**: Use old string-based syntax (existing code style)
```cpp
connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

connect(ui->licenseButton, SIGNAL(clicked()), this, SLOT(slotLicenseButtonClicked()));
```

**UI Files**: Always use Designer (.ui files) for dialogs/windows
- Access UI elements via `ui->elementName`
- Declare slots in header for UI connections

### Class Structure
```cpp
class MyDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MyDialog(QWidget *parent = 0);
    ~MyDialog();
    
    void publicMethod();

protected:
    void protectedMethod();

private slots:
    void on_actionSomething_triggered();  // Auto-connected
    void slotCustomSlot();                 // Manual slots

private:
    void privateHelperMethod();
    
    Ui::MyDialog *ui;                      // UI pointer first
    MemberType *m_pMember;                  // Then member variables
    bool m_bFlag;
};
```

### Error Handling
- Use Qt's error handling mechanisms
- Check process exit codes when running commands
- Use `QMessageBox` for user-facing errors
- Initialize pointers to `0` (not `nullptr` - legacy style)

### Platform Constraints
- Windows only - uses `netsh wlan` commands via QProcess
- Win32 resource file: `hostednetwork-gui.rc`
- Icon files in `images/` directory

### Resource Management
- Images and resources go in `hostednetwork-gui.qrc`
- Icons are PNG format in `images/` directory

## CI/CD

GitHub Actions workflow: `.github/workflows/cmake-windows-latest.yml`
- Runs on Windows Latest
- Uses Qt 5.15.2 with MSVC2019
- Build type: Release

## Build Output

Generated files to ignore (see `.gitignore`):
- `/build`, `/debug`, `/release` directories
- `*.exe`, `moc_*.cpp`, `ui_*.h`, `qrc_*.cpp`
- Qt Creator user files: `*.pro.user*`, `CMakeLists.txt.user*`
