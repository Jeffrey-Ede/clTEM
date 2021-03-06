//
// Created by jon on 04/04/18.
//

#include <structure/structureparameters.h>
#include "jsonutils.h"

namespace JSONUtils {

    SimulationManager JsonToManager(json& j) {
        bool dummy;
        return JsonToManager(j, dummy);
    }

    SimulationManager JsonToManager(json& j, bool& area_set)
    {
        SimulationManager man;
        area_set = false;
        // not sure there is a particularly easy way to go about this. Just go through all the options...
        try {
            auto mode = readJsonEntry<SimulationMode>(j, "mode", "id");
            if (mode == SimulationMode::None)
                mode = SimulationMode::CTEM;
            man.setMode( mode );
        } catch (json::out_of_range& e) {}

        try { man.setResolution( readJsonEntry<unsigned int>(j, "resolution") );
        } catch (json::out_of_range& e) {}

        try { man.setSliceThickness( readJsonEntry<float>(j, "slice thickness", "val") );
        } catch (json::out_of_range& e) {}

        try { man.setSliceOffset( readJsonEntry<float>(j, "slice offset", "val") );
        } catch (json::out_of_range& e) {}

        try { man.setFull3d( readJsonEntry<bool>(j, "full 3d", "state") );
        } catch (json::out_of_range& e) {}

        try { man.setFull3dInts( readJsonEntry<unsigned int>(j, "full 3d", "integrals") );
        } catch (json::out_of_range& e) {}

        try { man.setMaintainAreas( readJsonEntry<bool>(j, "maintain areas") );
        } catch (json::out_of_range& e) {}

        try { man.setStructureParameters( readJsonEntry<std::string>(j, "potentials") );
        } catch (json::out_of_range& e) {}

        try {
            auto p_xy_val = readJsonEntry<float>(j, "default padding", "xy", "val");
            man.setDefaultPaddingXY({-p_xy_val, p_xy_val});
        } catch (json::out_of_range& e) {}

        try {
            auto p_z_val = readJsonEntry<float>(j, "default padding", "z", "val");
            man.setDefaultPaddingZ({-p_z_val, p_z_val});
        } catch (json::out_of_range& e) {}

        //
        // Do all the microscope parameters stuff...
        //

        auto mp = man.getMicroscopeParams();

        try { mp->Voltage = readJsonEntry<float>(j, "microscope", "voltage", "val");
        } catch (json::out_of_range& e) {}

        try { mp->Aperture = readJsonEntry<float>(j, "microscope", "aperture", "val");
        } catch (json::out_of_range& e) {}

        try { mp->Alpha = readJsonEntry<float>(j, "microscope", "alpha", "val");
        } catch (json::out_of_range& e) {}

        try { mp->Delta = 10 * readJsonEntry<float>(j, "microscope", "delta", "val");
        } catch (json::out_of_range& e) {}

        try { mp->C10 = 10 * readJsonEntry<float>(j, "microscope", "aberrations", "C10", "val");
        } catch (json::out_of_range& e) {}

        try {
            mp->C12.Mag = 10 * readJsonEntry<float>(j, "microscope", "aberrations", "C12", "mag");
            mp->C12.Ang = (Constants::Pi / 180) * readJsonEntry<float>(j, "microscope", "aberrations", "C12", "ang");
        } catch (json::out_of_range& e) {}

        try {
            mp->C21.Mag = 10 * readJsonEntry<float>(j, "microscope", "aberrations", "C21", "mag");
            mp->C21.Ang = (Constants::Pi / 180) * readJsonEntry<float>(j, "microscope", "aberrations", "C21", "ang");
        } catch (json::out_of_range& e) {}

        try {
            mp->C23.Mag = 10 * readJsonEntry<float>(j, "microscope", "aberrations", "C23", "mag");
            mp->C23.Ang = (Constants::Pi / 180) * readJsonEntry<float>(j, "microscope", "aberrations", "C23", "ang");
        } catch (json::out_of_range& e) {}

        try { mp->C30 = 10000 * readJsonEntry<float>(j, "microscope", "aberrations", "C30", "val");
        } catch (json::out_of_range& e) {}

        try {
            mp->C32.Mag = 10000 * readJsonEntry<float>(j, "microscope", "aberrations", "C32", "mag");
            mp->C32.Ang = (Constants::Pi / 180) * readJsonEntry<float>(j, "microscope", "aberrations", "C32", "ang");
        } catch (json::out_of_range& e) {}

        try {
            mp->C34.Mag = 10000 * readJsonEntry<float>(j, "microscope", "aberrations", "C34", "mag");
            mp->C34.Ang = (Constants::Pi / 180) * readJsonEntry<float>(j, "microscope", "aberrations", "C34", "ang");
        } catch (json::out_of_range& e) {}

        try {
            mp->C41.Mag = 10000 * readJsonEntry<float>(j, "microscope", "aberrations", "C41", "mag");
            mp->C41.Ang = (Constants::Pi / 180) * readJsonEntry<float>(j, "microscope", "aberrations", "C41", "ang");
        } catch (json::out_of_range& e) {}

        try {
            mp->C43.Mag = 10000 * readJsonEntry<float>(j, "microscope", "aberrations", "C43", "mag");
            mp->C43.Ang = (Constants::Pi / 180) * readJsonEntry<float>(j, "microscope", "aberrations", "C43", "ang");
        } catch (json::out_of_range& e) {}

        try {
            mp->C45.Mag = 10000 * readJsonEntry<float>(j, "microscope", "aberrations", "C45", "mag");
            mp->C45.Ang = (Constants::Pi / 180) * readJsonEntry<float>(j, "microscope", "aberrations", "C45", "ang");
        } catch (json::out_of_range& e) {}

        try { mp->C50 = 10000 * readJsonEntry<float>(j, "microscope", "aberrations", "C50", "val");
        } catch (json::out_of_range& e) {}

        try {
            mp->C52.Mag = 10000 * readJsonEntry<float>(j, "microscope", "aberrations", "C52", "mag");
            mp->C52.Ang = (Constants::Pi / 180) * readJsonEntry<float>(j, "microscope", "aberrations", "C52", "ang");
        } catch (json::out_of_range& e) {}

        try {
            mp->C54.Mag = 10000 * readJsonEntry<float>(j, "microscope", "aberrations", "C54", "mag");
            mp->C54.Ang = (Constants::Pi / 180) * readJsonEntry<float>(j, "microscope", "aberrations", "C54", "ang");
        } catch (json::out_of_range& e) {}

        try {
            mp->C56.Mag = 10000 * readJsonEntry<float>(j, "microscope", "aberrations", "C56", "mag");
            mp->C56.Ang = (Constants::Pi / 180) * readJsonEntry<float>(j, "microscope", "aberrations", "C56", "ang");
        } catch (json::out_of_range& e) {}

        //
        // Phew, Ctem now
        //

        try { man.setCcdName(readJsonEntry<std::string>(j, "ctem", "ccd", "name"));
        } catch (json::out_of_range& e) {}

        try { man.setCcdDose(readJsonEntry<float>(j, "ctem", "ccd", "dose", "val"));
        } catch (json::out_of_range& e) {}

        try { man.setCcdBinning(readJsonEntry<int>(j, "ctem", "ccd", "binning"));
        } catch (json::out_of_range& e) {}

        try {
            auto xs = readJsonEntry<float>(j, "ctem", "area", "x", "start");
            auto xf = readJsonEntry<float>(j, "ctem", "area", "x", "finish");

            auto ys = readJsonEntry<float>(j, "ctem", "area", "y", "start");
            auto yf = readJsonEntry<float>(j, "ctem", "area", "y", "finish");

            SimulationArea ar(xs, xf, ys, yf);
            auto area = man.getSimulationArea();
            *area = ar;
            if (man.getMode() == SimulationMode::CTEM)
                area_set = true;
        } catch (json::out_of_range& e) {}

        //
        // STEM
        //

        try {
            auto xs = readJsonEntry<float>(j, "stem", "area", "x", "start");
            auto xf = readJsonEntry<float>(j, "stem", "area", "x", "finish");
            auto xp = readJsonEntry<int>(j, "stem", "scan", "x", "pixels");

            auto ys = readJsonEntry<float>(j, "stem", "area", "y", "start");
            auto yf = readJsonEntry<float>(j, "stem", "area", "y", "finish");
            auto yp = readJsonEntry<int>(j, "stem", "scan", "y", "pixels");

            auto pad = readJsonEntry<float>(j, "stem", "area", "padding", "val");

            StemArea ar(xs, xf, ys, yf, xp, yp, pad);
            auto area = man.getStemArea();
            *area = ar;
            if (man.getMode() == SimulationMode::STEM)
                area_set = true;
        } catch (json::out_of_range& e) {}

        try { man.setTdsRunsStem(readJsonEntry<unsigned int>(j, "stem", "tds", "configurations"));
        } catch (json::out_of_range& e) {}

        try { man.setTdsEnabledStem(readJsonEntry<bool>(j, "stem", "tds", "enabled"));
        } catch (json::out_of_range& e) {}

        try { man.setParallelPixels(readJsonEntry<unsigned int>(j, "stem", "concurrent pixels"));
        } catch (json::out_of_range& e) {}

        // detectors...

        try {
            json det_section = readJsonEntry<json>(j, "stem", "detectors");
            for (json::iterator it = det_section.begin(); it != det_section.end(); ++it) {
                std::string entry = it.key();
                try{
                    auto inner = readJsonEntry<unsigned int>(det_section, entry, "radius", "inner");
                    auto outer = readJsonEntry<unsigned int>(det_section, entry, "radius", "outer");
                    auto xc = readJsonEntry<unsigned int>(det_section, entry, "centre", "x");
                    auto yc = readJsonEntry<unsigned int>(det_section, entry, "centre", "y");

                    StemDetector d(entry, inner, outer, xc, yc);

                    man.getDetectors().push_back(d);

                } catch (json::out_of_range& e) {}
            }

        } catch (json::out_of_range& e) {}

        //
        // CBED
        //

        try {
            auto x = readJsonEntry<float>(j, "cbed", "position", "x");
            auto y = readJsonEntry<float>(j, "cbed", "position", "y");
            auto pad = readJsonEntry<float>(j, "cbed", "position", "padding");

            CbedPosition ar(x, y, pad);
            auto area = man.getCBedPosition();
            *area = ar;
            if (man.getMode() == SimulationMode::CBED)
                area_set = true; // I don't know if this one matters...
        } catch (json::out_of_range& e) {}

        try { man.setTdsRunsCbed(readJsonEntry<unsigned int>(j, "cbed", "tds", "configurations"));
        } catch (json::out_of_range& e) {}

        try { man.setTdsEnabledCbed(readJsonEntry<bool>(j, "cbed", "tds", "enabled"));
        } catch (json::out_of_range& e) {}

        *(man.getThermalVibrations()) = JsonToThermalVibrations(j);

        return man;
    }

    ThermalVibrations JsonToThermalVibrations(json& j) {

        ThermalVibrations out_therms;

        bool force_default = false;
        bool override_file = false;
        float def = 0.0f;

        std::vector<float> vibs;
        std::vector<int> els;

        try { force_default = readJsonEntry<bool>(j, "thermal parameters", "force default");
        } catch (json::out_of_range& e) {}

        try { override_file = readJsonEntry<bool>(j, "thermal parameters", "override file");
        } catch (json::out_of_range& e) {}

        try { def = readJsonEntry<float>(j, "thermal parameters", "default");
        } catch (json::out_of_range& e) {}

        try {
            json element_section = readJsonEntry<json>(j, "thermal parameters", "values");
            for (json::iterator it = element_section.begin(); it != element_section.end(); ++it) {
                std::string element = it.key();
                try{
                    auto v = readJsonEntry<float>(element_section, element);
                    els.emplace_back( Utils::ElementSymbolToNumber(element) );
                    vibs.emplace_back(v);
                } catch (json::out_of_range& e) {}
            }

        } catch (json::out_of_range& e) {}

        out_therms.setVibrations(def, els, vibs);
        out_therms.force_defined = override_file;
        out_therms.force_default = force_default;

        return out_therms;
    }

    json FullManagerToJson(SimulationManager& man) {
        // this gets pretty much everything that is set
        json j = BasicManagerToJson(man, true);

        for (auto det : man.getDetectors())
        {
            j["stem"]["detectors"][det.name] = JSONUtils::stemDetectorToJson(det);
        }

        return j;
    }

    json BasicManagerToJson(SimulationManager& man, bool force_all) {

        json j;

        // no file input here as it is not always needed

        auto mode = man.getMode();
        j["mode"]["id"] = mode;
        j["mode"]["name"] = man.getModeString();

        j["potentials"] = man.getStructureParametersName();

        j["resolution"] = man.getResolution();

        j["slice thickness"]["val"] = man.getSliceThickness();
        j["slice thickness"]["units"] = "Å";

        j["slice offset"]["val"] = man.getSliceOffset();
        j["slice offset"]["units"] = "Å";

        j["maintain areas"] = man.getMaintainAreas();


        auto xl = man.getPaddedSimLimitsX();
        auto yl = man.getPaddedSimLimitsY();
        auto zl = man.getPaddedStructLimitsZ(); // z never changes, so always is struct limits

        // padding is always plus/minus one value, with the second element ([1]) being positive
        auto xp = man.getPaddingX()[1];
        auto yp = man.getPaddingY()[1];
        auto zp = man.getPaddingZ()[1];

        j["simulation area"]["x"]["start"] = xl[0];
        j["simulation area"]["x"]["finish"] = xl[1];
        j["simulation area"]["x"]["padding"] = xp;
        j["simulation area"]["x"]["units"] = "Å";
        j["simulation area"]["y"]["start"] = yl[0];
        j["simulation area"]["y"]["finish"] = yl[1];
        j["simulation area"]["y"]["padding"] = yp;
        j["simulation area"]["y"]["units"] = "Å";
        j["simulation area"]["z"]["start"] = zl[0];
        j["simulation area"]["z"]["finish"] = zl[1];
        j["simulation area"]["z"]["padding"] = zp;
        j["simulation area"]["z"]["units"] = "Å";


        auto p_z_d_val = man.getDefaultPaddingZ();
        auto p_xy_d_val = man.getDefaultPaddingXY();

        j["default padding"]["z"]["val"] = p_z_d_val[1];
        j["default padding"]["z"]["units"] = "Å";
        j["default padding"]["xy"]["val"] = p_xy_d_val[1];
        j["default padding"]["xy"]["units"] = "Å";

        // TODO: could put some pixel scale things here for convenience? (would have to distinguish between diff maybe?)

        bool f3d = man.isFull3d();

        if(f3d || force_all) {
            j["full 3d"]["state"] = f3d;
            j["full 3d"]["integrals"] = man.getFull3dInts();
        } else
            j["full 3d"]["state"] = f3d;

        auto mp = man.getMicroscopeParams();

        j["microscope"]["voltage"]["val"] = mp->Voltage;
        j["microscope"]["voltage"]["units"] = "kV";

        // TODO: check which parameters are relevant to which modes
        // TODO: get whether CTEM is image, EW or diff...

        // apert
        j["microscope"]["aperture"]["val"] = mp->Aperture;
        j["microscope"]["aperture"]["units"] = "mrad";

        if (mode == SimulationMode::CTEM || force_all) {
            // alpha
            j["microscope"]["alpha"]["val"] = mp->Alpha;
            j["microscope"]["alpha"]["units"] = "mrad";

            // delta
            j["microscope"]["delta"]["val"] = mp->Delta / 10;
            j["microscope"]["delta"]["units"] = "nm";
        }

        // aberration values
        j["microscope"]["aberrations"]["C10"]["val"] = mp->C10 / 10;
        j["microscope"]["aberrations"]["C10"]["units"] = "nm";
        j["microscope"]["aberrations"]["C12"]["mag"] = mp->C12.Mag / 10;
        j["microscope"]["aberrations"]["C12"]["ang"] = mp->C12.Ang * (180 / Constants::Pi);
        j["microscope"]["aberrations"]["C12"]["units"] = "nm, °";

        j["microscope"]["aberrations"]["C21"]["mag"] = mp->C21.Mag / 10;
        j["microscope"]["aberrations"]["C21"]["ang"] = mp->C21.Ang * (180 / Constants::Pi);
        j["microscope"]["aberrations"]["C21"]["units"] = "nm, °";
        j["microscope"]["aberrations"]["C23"]["mag"] = mp->C23.Mag / 10;
        j["microscope"]["aberrations"]["C23"]["ang"] = mp->C23.Ang * (180 / Constants::Pi);
        j["microscope"]["aberrations"]["C23"]["units"] = "nm, °";

        j["microscope"]["aberrations"]["C30"]["val"] = mp->C30 / 10000;
        j["microscope"]["aberrations"]["C30"]["units"] = "μm";
        j["microscope"]["aberrations"]["C32"]["mag"] = mp->C32.Mag / 10000;
        j["microscope"]["aberrations"]["C32"]["ang"] = mp->C32.Ang * (180 / Constants::Pi);
        j["microscope"]["aberrations"]["C32"]["units"] = "μm, °";
        j["microscope"]["aberrations"]["C34"]["mag"] = mp->C34.Mag / 10000;
        j["microscope"]["aberrations"]["C34"]["ang"] = mp->C34.Ang * (180 / Constants::Pi);
        j["microscope"]["aberrations"]["C34"]["units"] = "μm, °";

        j["microscope"]["aberrations"]["C41"]["mag"] = mp->C41.Mag / 10000;
        j["microscope"]["aberrations"]["C41"]["ang"] = mp->C41.Ang * (180 / Constants::Pi);
        j["microscope"]["aberrations"]["C41"]["units"] = "μm, °";
        j["microscope"]["aberrations"]["C43"]["mag"] = mp->C43.Mag / 10000;
        j["microscope"]["aberrations"]["C43"]["ang"] = mp->C43.Ang * (180 / Constants::Pi);
        j["microscope"]["aberrations"]["C43"]["units"] = "μm, °";
        j["microscope"]["aberrations"]["C45"]["mag"] = mp->C45.Mag / 10000;
        j["microscope"]["aberrations"]["C45"]["ang"] = mp->C45.Ang * (180 / Constants::Pi);
        j["microscope"]["aberrations"]["C45"]["units"] = "μm, °";

        j["microscope"]["aberrations"]["C50"]["val"] = mp->C50 / 10000;
        j["microscope"]["aberrations"]["C50"]["units"] = "μm";
        j["microscope"]["aberrations"]["C52"]["mag"] = mp->C52.Mag / 10000;
        j["microscope"]["aberrations"]["C52"]["ang"] = mp->C52.Ang * (180 / Constants::Pi);
        j["microscope"]["aberrations"]["C52"]["units"] = "μm, °";
        j["microscope"]["aberrations"]["C54"]["mag"] = mp->C54.Mag / 10000;
        j["microscope"]["aberrations"]["C54"]["ang"] = mp->C54.Ang * (180 / Constants::Pi);
        j["microscope"]["aberrations"]["C54"]["units"] = "μm, °";
        j["microscope"]["aberrations"]["C56"]["mag"] = mp->C56.Mag / 10000;
        j["microscope"]["aberrations"]["C56"]["ang"] = mp->C56.Ang * (180 / Constants::Pi);
        j["microscope"]["aberrations"]["C56"]["units"] = "μm, °";

        // If CTEM, get dose/CCD stuff
        if (mode == SimulationMode::CTEM || force_all)
        {
            // cropped padding entry will be added at the time of saving

            if (CCDParams::nameExists(man.getCcdName()) || force_all) {
                j["ctem"]["ccd"]["name"] = man.getCcdName();
                j["ctem"]["ccd"]["dose"]["val"] = man.getCcdDose();
                j["ctem"]["ccd"]["dose"]["units"] = "e- per square Å";
                j["ctem"]["ccd"]["binning"] = man.getCcdBinning();
            } else {
                j["ctem"]["ccd"] = "Perfect";
            }

            j["ctem"]["area"]["x"]["start"] = man.getCtemArea().getRawLimitsX()[0];
            j["ctem"]["area"]["x"]["finish"] = man.getCtemArea().getRawLimitsX()[1];

            j["ctem"]["area"]["y"]["start"] = man.getCtemArea().getRawLimitsY()[0];
            j["ctem"]["area"]["y"]["finish"] = man.getCtemArea().getRawLimitsY()[1];
        }

        // If STEM, get scan info, TDS info detector info will be added later if needed
        if (mode == SimulationMode::STEM || force_all)
        {
            auto sa = man.getStemArea();
            j["stem"]["area"]["x"]["start"] = sa->getRawLimitsX()[0];
            j["stem"]["area"]["x"]["finish"] = sa->getRawLimitsX()[1];
            j["stem"]["scan"]["x"]["pixels"] = sa->getPixelsX();;
            j["stem"]["area"]["x"]["units"] = "Å";
            j["stem"]["area"]["y"]["start"] = sa->getRawLimitsY()[0];
            j["stem"]["area"]["y"]["finish"] = sa->getRawLimitsY()[1];
            j["stem"]["scan"]["y"]["pixels"] = sa->getPixelsY();
            j["stem"]["area"]["y"]["units"] = "Å";
            j["stem"]["area"]["padding"]["val"] = sa->getPadding();
            j["stem"]["area"]["padding"]["units"] = "Å";

            // stem detector bit...

            j["stem"]["concurrent pixels"] = man.getParallelPixels();

            if (force_all) {
                j["stem"]["tds"]["configurations"] = man.getStoredTdsRunsStem();
                j["stem"]["tds"]["enabled"] = man.getTdsEnabledStem();
            }
            else
                j["stem"]["tds"]["configurations"] = man.getTdsRunsStem();
        }

        // If CBED, get position info and TDS info
        if (mode == SimulationMode::CBED || force_all)
        {
            j["cbed"]["position"]["x"] = man.getCBedPosition()->getXPos();
            j["cbed"]["position"]["y"] = man.getCBedPosition()->getYPos();
            j["cbed"]["position"]["padding"] = man.getCBedPosition()->getPadding();
            j["cbed"]["position"]["units"] = "Å";
            if (force_all) {
                j["cbed"]["tds"]["configurations"] = man.getStoredTdsRunsCbed();
                j["cbed"]["tds"]["enabled"] = man.getTdsEnabledCbed();
            }
            else
                j["cbed"]["tds"]["configurations"] = man.getTdsRunsCbed();
        }

        // don't export if we have file defined vibrations and no override
        bool export_thermals = true;
        if (man.getStructure()) // structure does not always exist
            export_thermals = !(man.getStructure()->isThermalFileDefined() && !man.getThermalVibrations()->force_default && !man.getThermalVibrations()->force_defined);

        if (export_thermals || force_all) {
            if (mode == SimulationMode::CBED || mode == SimulationMode::STEM || force_all)
                j["thermal parameters"] = thermalVibrationsToJson(man);
        } else {
            j["thermal parameters"] = "input file defined";
        }

        return j;
    }

    json stemDetectorToJson(StemDetector d) {
        json j;

        j["radius"]["inner"] = d.inner;
        j["radius"]["outer"] = d.outer;
        j["radius"]["units"] = "mrad";
        j["centre"]["x"] = d.xcentre;
        j["centre"]["y"] = d.ycentre;
        j["centre"]["units"] = "mrad";

        return j;
    }

    json thermalVibrationsToJson(SimulationManager& man) {
        json j;

        j["force default"] = man.getThermalVibrations()->force_default;
        j["override file"] = man.getThermalVibrations()->force_defined;

        j["default"] = man.getThermalVibrations()->getDefault();
        j["units"] = "Å²";

        auto els = man.getThermalVibrations()->getDefinedElements();
        auto vibs = man.getThermalVibrations()->getDefinedVibrations();

        if (els.size() != vibs.size())
            throw std::runtime_error("cannot write thermal parameters to json file: element and displacement vectors have different size");

        for(int i = 0; i < els.size(); ++i) {
            j["values"][ Utils::NumberToElementSymbol(els[i]) ] = vibs[i];
        }

        return j;
    }

}