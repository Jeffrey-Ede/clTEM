#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <controls/statuslayout.h>
#include <frames/simulationframe.h>
#include <frames/stemframe.h>
#include <frames/cbedframe.h>
#include <controls/flattitlebar.h>
#include <controls/borderlesswindow.h>

#include "simulationmanager.h"
#include "simulationthread.h"

#include "utilities/logging.h"
#include "utilities/simutils.h"

class CbedFrame;
class SimulationFrame;
class StemFrame;

namespace Ui {
class MainWindow;
}

class MainWindow : public BorderlessWindow
{
    Q_OBJECT

signals:
    void sliceProgressUpdated(float);
    void totalProgressUpdated(float);

    void imagesReturned(SimulationManager);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    std::shared_ptr<SimulationManager> Manager;

    std::shared_ptr<MicroscopeParameters> getMicroscopeParams() {return Manager->getMicroscopeParams();}
    std::shared_ptr<CrystalStructure> getStructure() {return Manager->getStructure();}
    std::shared_ptr<SimulationArea> getSimulationArea() {return Manager->getSimulationArea();}
    std::vector<StemDetector>& getDetectors() {return Manager->getDetectors();}
    std::shared_ptr<StemArea> getStemArea() {return Manager->getStemArea();}

    void setDetectors();

    void updateRanges();

    void updateSlicesProgress(float prog);
    void updateTotalProgress(float prog);

    void updateImages(SimulationManager sm);

    void updateManagerFromGui();

    // these are to make conencting some signals/slots in dialogs much easier
    SimulationFrame* getSimulationFrame();
    StemFrame* getStemFrame();
    CbedFrame* getCbedFrame();

public slots:
    void updateScales();

    void updateVoltageMrad(float voltage);

    void set_active_mode(int mode);

private slots:
    void on_actionOpen_triggered();

    void on_actionOpenCL_triggered();

    void on_actionTheme_triggered();

    void on_actionGeneral_triggered();

    void on_actionImport_parameters_triggered();

    void on_actionExport_parameters_triggered();

    void on_actionImport_default_triggered(bool preserve_ui = true);

    void on_actionExport_default_triggered();

    void on_actionShow_default_triggered();

    void on_actionSet_area_triggered();

    void on_actionAberrations_triggered();

    void on_actionThermal_scattering_triggered();

    void on_actionSimulate_EW_triggered();

    void cancel_simulation();

    void set_ctem_crop(bool state);

    void resolution_changed(int resolution);

    void on_twMode_currentChanged(int index);

    void sliceProgressChanged(float prog);

    void totalProgressChanged(float prog);

    void imagesChanged(SimulationManager sm);

    void setUiActive(bool active);

    void simulationComplete();

    void simulationFailed();

    void saveTiff();

    void saveBmp();

private:
    FlatTitleBar *m_title;

    StatusLayout* StatusBar;

    QMutex Progress_Mutex, Image_Mutex;

    std::shared_ptr<SimulationThread> SimThread;

    std::vector<clDevice> Devices;

    void loadSavedOpenClSettings();

    void loadExternalSources();

    void updateGuiFromManager();

protected:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
