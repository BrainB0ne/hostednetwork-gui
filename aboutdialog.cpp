/*
 * Spotweb Filter Creator
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

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include "licensedialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    m_pLicenseDlg = 0;

    ui->buildDateLabel->setText(tr("Build Date: %1 - %2").arg(__DATE__).arg(__TIME__));
    ui->versionLabel->setText(tr("Version: %1").arg("0.1.0"));

    connect(ui->licenseButton, SIGNAL(clicked()), this, SLOT(slotLicenseButtonClicked()));
}

AboutDialog::~AboutDialog()
{
    if(m_pLicenseDlg) delete m_pLicenseDlg;

    delete ui;
}

void AboutDialog::slotLicenseButtonClicked()
{
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    if(!m_pLicenseDlg)
    {
        m_pLicenseDlg = new LicenseDialog(this);
    }

    m_pLicenseDlg->show();
    m_pLicenseDlg->initialize();

    QApplication::restoreOverrideCursor();
}
