#include <QtGui/QRegExpValidator>
#include <dialogs/settings/settingsdialog.h>
#include "globalsimsettingsframe.h"
#include "ui_globalsimsettingsframe.h"

GlobalSimSettingsFrame::GlobalSimSettingsFrame(QWidget *parent, std::shared_ptr<SimulationManager> simManager) :
    QWidget(parent), ui(new Ui::GlobalSimSettingsFrame), Manager(simManager)
{
    ui->setupUi(this);

    auto parent_dlg = dynamic_cast<GlobalSettingsDialog*>(parentWidget());
    connect(parent_dlg, &GlobalSettingsDialog::okSignal, this, &GlobalSimSettingsFrame::dlgOk_clicked);
    connect(parent_dlg, &GlobalSettingsDialog::cancelSignal, this, &GlobalSimSettingsFrame::dlgCancel_clicked);
    connect(parent_dlg, &GlobalSettingsDialog::applySignal, this, &GlobalSimSettingsFrame::dlgApply_clicked);

    ui->edtPaddingXY->setUnits("Å");
    ui->edtPaddingZ->setUnits("Å");

    QRegExpValidator* pIntValidator = new QRegExpValidator(QRegExp("[+]?\\d*"));

    QRegExpValidator* pValidator = new QRegExpValidator(QRegExp(R"([+]?(\d*(?:\.\d*)?(?:[eE]([+\-]?\d+)?)>)*)"));

    ui->edt3dIntegrals->setValidator(pIntValidator);
    ui->edtParallelPx->setValidator(pIntValidator);
    ui->edtPaddingXY->setValidator(pValidator);
    ui->edtPaddingZ->setValidator(pValidator);

    int three_d_int = simManager->getFull3dInts();
    int num_parallel = simManager->getParallelPixels();

    ui->edt3dIntegrals->setText(QString::number(three_d_int));
    ui->edtParallelPx->setText(QString::number(num_parallel));

    ui->edtPaddingXY->setText(QString::number(Manager->getDefaultPaddingXY()[1]));
    ui->edtPaddingZ->setText(QString::number(Manager->getDefaultPaddingZ()[1]));

    // make the label widths the same so they line up
    auto w1 = ui->lbl3d->width();
    auto w2 = ui->lblParallel->width();
    auto w3 = ui->lblParameters->width();
    auto w4 = ui->lblPaddingXY->width();
    auto w5 = ui->lblPaddingZ->width();
    auto w = std::max(std::max(w1, w2), std::max(w3, std::max(w4, w5)));
    ui->lbl3d->setMinimumWidth(w);
    ui->lblParallel->setMinimumWidth(w);
    ui->lblParameters->setMinimumWidth(w);
    ui->lblPaddingXY->setMinimumWidth(w);
    ui->lblPaddingZ->setMinimumWidth(w);

    populateParamsCombo();
}

GlobalSimSettingsFrame::~GlobalSimSettingsFrame() {
    delete ui;
}

void GlobalSimSettingsFrame::dlgCancel_clicked() {
    // don't need to do anything, just return
    parentWidget()->close();
}

void GlobalSimSettingsFrame::dlgOk_clicked() {
    // same as clicking apply then closing the dialog
    dlgApply_clicked();
    parentWidget()->close();
}

void GlobalSimSettingsFrame::dlgApply_clicked() {
    unsigned int n_3d = ui->edt3dIntegrals->text().toUInt();
    unsigned int n_parallel = ui->edtParallelPx->text().toUInt();
    std::string param_name = ui->cmbParams->currentText().toStdString();
    float pad_xy = ui->edtPaddingXY->text().toFloat();
    float pad_z = ui->edtPaddingZ->text().toFloat();

    Manager->setFull3dInts(n_3d);
    Manager->setParallelPixels(n_parallel);
    Manager->setStructureParameters(param_name);
    Manager->setDefaultPaddingXY({-pad_xy, pad_xy});
    Manager->setDefaultPaddingZ({-pad_z, pad_z});
}

void GlobalSimSettingsFrame::populateParamsCombo() {
    auto names = StructureParameters::getNames();

    auto cur = Manager->getStructureParametersName();

    unsigned int current = 0;
    for (unsigned int i = 0; i < names.size(); ++i) {
        if (names[i] == cur)
            current = i;
        ui->cmbParams->addItem(QString::fromStdString(names[i]));
    }

    ui->cmbParams->setCurrentIndex(current);
}