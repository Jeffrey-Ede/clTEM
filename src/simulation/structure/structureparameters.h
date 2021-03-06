#include <utility>

#include <utility>

#ifndef CLTEM_STRUCTUREPARAMETERS_H
#define CLTEM_STRUCTUREPARAMETERS_H

#include <vector>
#include <mutex>
#include <algorithm>

// This class is purely static, and is mainly used for reading in the required data and storing it.
// When it is actually needed, it is copied to the SimulationManager classes so they have their own copy
// and this can be edited whilst a simulation is running...

struct Parameterisation {
    Parameterisation() : Name(""), Parameters(), Max_Atomic_Number(0) {}
    Parameterisation(std::string _name, std::vector<float> _params, unsigned int _max) : Name(std::move(_name)), Parameters(std::move(_params)), Max_Atomic_Number(_max) {}

    std::string Name;

    std::vector<float> Parameters;

    unsigned int Max_Atomic_Number;

    bool operator==(const std::string &_name) { return _name == Name; }
};

class StructureParameters
{
private:
    static std::vector<Parameterisation> Params;

    static std::mutex mtx;

public:
    static void setParams(const std::vector<float> &p, const std::string &name, unsigned int atom_count) {
        std::lock_guard<std::mutex> lck(mtx);
        // test if the name already exists
        if (std::find(Params.begin(), Params.end(), name)!= Params.end())
            throw std::runtime_error("Error adding duplicate parameter file");

        Params.emplace_back(name, p, atom_count);
    }

    static Parameterisation getParameter(const std::string &name) {
        std::lock_guard<std::mutex> lck(mtx);

        auto ind = std::find(Params.begin(), Params.end(), name);
        if (ind == Params.end())
            return Parameterisation();

        int Current = (int) (ind - Params.begin());

        return Params[Current];
    }

    static std::vector<float> getParameterData(const std::string &name) {
        // I could cal the getParameter function, but I will try to lock the mutex twice...
        std::lock_guard<std::mutex> lck(mtx);

        auto ind = std::find(Params.begin(), Params.end(), name);
        if (ind == Params.end())
            return std::vector<float>();

        int Current = (int) (ind - Params.begin());

        return Params[Current].Parameters;
    }


    static std::vector<std::string> getNames() {
        std::lock_guard<std::mutex> lck(mtx);
        std::vector<std::string> names;

        for (const auto &p : Params)
            names.push_back(p.Name);
        return names;
    }
};

#endif //CLTEM_STRUCTUREPARAMETERS_H
