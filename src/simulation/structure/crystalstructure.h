#ifndef CRYSTALSTRUCTURE_H
#define CRYSTALSTRUCTURE_H

#include <vector>
#include <string>
#include <valarray>
#include <random>

#include "utilities/commonstructs.h"

#include "thermalvibrations.h"

#include "atom.h"
#include "cif/cifreader.h"
#include "cif/supercell.h"

namespace FileFormat {
    enum FileFormat {
        XYZ,
        CIF
    };
}

class CrystalStructure
{
public:
private:
    /// Vector of atoms with coordinates in Angstroms
    std::vector<AtomSite> Atoms;

    /// Vector of all the different atomic numebr we have in our structure
//    std::vector<int> AtomTypes;

    /// Filepath to to file we opened
    std::string filePath;

    bool file_defined_thermals;

    /// Use to conver the structure/file units to Angstrom
    float ScaleFactor;

    /// Spacial ;imits of our structure
    float MaxX;
    float MinX;
    float MaxY;
    float MinY;
    float MaxZ;
    float MinZ;

    /// MAx atomic number - used to see our parameterisation covers this (assumes parameterisation does not have gaps)
    unsigned int MaxAtomicNumber;
    unsigned int AtomCount;

    std::mt19937 rng;
    std::uniform_real_distribution<> dist;

    void resetLimits();
    void updateLimits(const Atom &a);

    void processOccupancyList(std::vector<AtomSite> &aList);

    void addAtom(AtomSite a);

    void processAtomList(std::vector<std::string> A, std::vector<float> x, std::vector<float> y, std::vector<float> z, std::vector<float> occ, std::vector<float> ux, std::vector<float> uy, std::vector<float> uz);

public:
    // mostly for opening .xyz files, but will handle .cif
    explicit CrystalStructure(std::string &fPath, CIF::SuperCellInfo info = CIF::SuperCellInfo());

    // only for opening cif files
    explicit CrystalStructure(CIF::CIFReader cif, CIF::SuperCellInfo info);

    /// Loads the given xyz file getting the atom coordinates in Angstroms
    /// \param fPath - path to .xyz file to open
    void openXyz(std::string fPath);

    void openCif(std::string fPath, CIF::SuperCellInfo info);
    void openCif(CIF::CIFReader cif, CIF::SuperCellInfo info);

    std::string getFileName() {return filePath;}

    std::vector<AtomSite> getAtoms() {return Atoms;}

    int getAtomCountInRange(float xs, float xf, float ys, float yf);

    std::valarray<float> getLimitsX() {return {MinX, MaxX};}

    std::valarray<float> getLimitsY() {return {MinY, MaxY};}

    std::valarray<float> getLimitsZ() {return {MinZ, MaxZ};}

    unsigned int getMaxAtomicNumber() {return MaxAtomicNumber;}

    bool isThermalFileDefined() { return file_defined_thermals; }

//    std::vector<int> getAtomsTypes() {return AtomTypes;}
};

#endif // CRYSTALSTRUCTURE_H
