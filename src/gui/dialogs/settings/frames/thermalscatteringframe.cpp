#include <utils/stringutils.h>
#include <dialogs/settings/settingsdialog.h>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidgetItem>
#include <structure/thermalvibrations.h>
#include "thermalscatteringframe.h"
#include "ui_thermalscatteringframe.h"

ThermalScatteringFrame::ThermalScatteringFrame(QWidget *parent, std::shared_ptr<SimulationManager> simManager) :
    QWidget(parent), ui(new Ui::ThermalScatteringFrame), Manager(simManager)
{
    ui->setupUi(this);

    // fiddle with the table
    ui->tblDisplacements->setColumnWidth(0, 80);
    ui->tblDisplacements->setColumnWidth(1, 200);
    ui->tblDisplacements->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // sort out text boxes units and so on
    QRegExpValidator* pValidator = new QRegExpValidator(QRegExp(R"([+]?(\d*(?:\.\d*)?(?:[eE]([+\-]?\d+)?)>)*)"));

    ui->edtDefault->setValidator(pValidator);
    ui->edtDisplacement->setValidator(pValidator);

    ui->edtDefault->setUnits("Å²");
    ui->edtDisplacement->setUnits("Å²");

    // set the text box values
    ui->edtDefault->setText( QString::number( Manager->getThermalVibrations()->getDefault() ) );
    ui->edtDisplacement->setText("0.0");

    // fill the combo box from our map of atomic numbers to symbols
    // http://www.cplusplus.com/forum/beginner/123379/

    for (const auto &it : Utils::VectorSymbolToNumber) {
        ui->cmbElement->addItem( QString::fromStdString(it.first));
    }

    ui->chkForceDefault->setChecked(Manager->getThermalVibrations()->force_default);
    ui->chkOverride->setChecked(Manager->getThermalVibrations()->force_defined);

    // add the defined elements to the table...
    auto el = Manager->getThermalVibrations()->getDefinedElements();
    auto vib = Manager->getThermalVibrations()->getDefinedVibrations();

    // shouldn't be needed, but just in case...
    if (el.size() != vib.size())
        throw(std::runtime_error("Cannot get thermal vibrations with different elements and vibration vector sizes"));

    for (int i = 0; i < el.size(); ++i) {
        std::string temp_element = Utils::NumberToElementSymbol(el[i]);
        addItemToList( temp_element , vib[i]);
    }

    // connect up our OK, etc... buttons
    auto parent_dlg = dynamic_cast<ThermalScatteringDialog*>(parentWidget());
    connect(parent_dlg, &ThermalScatteringDialog::okSignal, this, &ThermalScatteringFrame::dlgOk_clicked);
    connect(parent_dlg, &ThermalScatteringDialog::cancelSignal, this, &ThermalScatteringFrame::dlgCancel_clicked);
    connect(parent_dlg, &ThermalScatteringDialog::applySignal, this, &ThermalScatteringFrame::dlgApply_clicked);
}

ThermalScatteringFrame::~ThermalScatteringFrame()
{
    delete ui;
}

void ThermalScatteringFrame::dlgCancel_clicked()
{
    // don't need to do anything, just return
    auto * dlg = dynamic_cast<ThermalScatteringDialog*>(parentWidget());
    dlg->reject();
}

void ThermalScatteringFrame::dlgOk_clicked()
{
    // same as clicking apply then closing the dialog
    if(dlgApply_clicked())
    {
        auto * dlg = dynamic_cast<ThermalScatteringDialog*>(parentWidget());
        dlg->accept();
    }
}

bool ThermalScatteringFrame::dlgApply_clicked()
{
    // get our default, easy...
    float def = ui->edtDefault->text().toFloat();

    // create vectors of our explicitly defined elements
    int nRows = ui->tblDisplacements->rowCount();

    std::vector<int> elements(nRows);
    std::vector<float> displacements(nRows);

    for (int i = 0; i < nRows; ++i) {
        std::string temp_el = ui->tblDisplacements->item(i, 0)->text().toStdString();
        elements[i] = Utils::ElementSymbolToNumber(temp_el);
        displacements[i] = ui->tblDisplacements->item(i, 1)->text().toFloat();
    }

    Manager->getThermalVibrations()->setVibrations(def, elements, displacements);

    Manager->getThermalVibrations()->force_defined = ui->chkOverride->isChecked();
    Manager->getThermalVibrations()->force_default = ui->chkForceDefault->isChecked();

    return true;
}

void ThermalScatteringFrame::addItemToList(std::string el, float vib) {
    int n = ui->tblDisplacements->rowCount();

    bool found = false;
    for (int i = 0; i < n && !found; ++i) {
        if (el == ui->tblDisplacements->item(i, 0)->text().toStdString()) {
            n = i;
            found = true;
        }
    }

    if (!found)
        ui->tblDisplacements->insertRow(n);

    auto *cell_0 = new QTableWidgetItem();
    cell_0->setTextAlignment(Qt::AlignCenter);
    cell_0->setText(QString::fromStdString(el));

    auto cell_1 = cell_0->clone();
//    cell_1->setTextAlignment(Qt::AlignCenter);
    cell_1->setText(Utils_Qt::numToQString(vib));

    ui->tblDisplacements->setItem(n, 0, cell_0);
    ui->tblDisplacements->setItem(n, 1, cell_1);
}

void ThermalScatteringFrame::on_btnAdd_clicked() {
    std::string el = ui->cmbElement->currentText().toStdString();

    float vib = ui->edtDisplacement->text().toFloat();

    addItemToList(el, vib);
}

void ThermalScatteringFrame::on_btnDelete_clicked() {
    QList<QTableWidgetItem *> selection = ui->tblDisplacements->selectedItems();

    std::vector<int> toRemove;
    for (auto i : selection)
        if(i->column() == 0)
            toRemove.push_back(i->row());

    std::sort(toRemove.begin(), toRemove.end());

    int n = 0;
    for (int i : toRemove) {
        ui->tblDisplacements->removeRow(i - n);
        ++n;
    }
}