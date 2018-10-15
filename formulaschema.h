/* 
 * File:   formulaschema.h
 * Author: kuestere
 *
 * Created on 1. Oktober 2018, 19:28
 */

#ifndef FORMULASCHEMA_H
#define FORMULASCHEMA_H

#include <glibmm.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "formulaparser.h"

using namespace std;

class FormulaParser;

class FormulaSchema {
public:
    FormulaSchema();
    FormulaSchema(const FormulaSchema& orig);
    virtual ~FormulaSchema();

    double totalMass = 0.0;

    struct element {
        string symbol;
        Glib::ustring name;
        double mass;
    };

    // official <https://iupac.org/what-we-do/periodic-table-of-elements/>
    // latin <https://la.wikipedia.org/wiki/Systema_periodicum>
    std::vector<element> elements = {
        {"Ac", "Actinium", 227.0278},
        {"Ag", "Argentum", 107.8682},
        {"Al", "Aluminium", 26.981539},
        {"Ar", "Argon", 39.948},
        {"As", "Arsenicum", 74.92159},
        {"At", "Astatinum", 209.9871},
        {"Au", "Aurum", 196.96654},
        {"B", "Borium", 10.811},
        {"Ba", "Barium", 137.327},
        {"Be", "Beryllium", 9.012182},
        {"Bi", "Bismuthum", 208.98037},
        {"Br", "Bromum", 79.904},
        {"C", "Carbonium", 12.011},
        {"Ca", "Calcium", 40.078},
        {"Cd", "Cadmium", 112.411},
        {"Ce", "Cerium", 140.115},
        {"Cl", "Chlorum", 35.4527},
        {"Co", "Cobaltum", 58.9332},
        {"Cr", "Chromium", 51.9961},
        {"Cs", "Caesium", 132.90543},
        {"Cu", "Cuprum", 63.546},
        {"Dy", "Dysprosium", 162.5},
        {"Er", "Erbium", 167.26},
        {"Eu", "Europium", 151.965},
        {"F", "Fluorum", 18.9984032},
        {"Fe", "Ferrum", 55.847},
        {"Fr", "Francium", 223.0197},
        {"Ga", "Gallium", 69.723},
        {"Gd", "Gadolinium", 157.25},
        {"Ge", "Germanium", 72.61},
        {"H", "Hydrogenium", 1.00794},
        {"He", "Helium", 4.002602},
        {"Hf", "Hafnium", 178.49},
        {"Hg", "Hydrargyrum", 200.59},
        {"Ho", "Holmium", 164.93032},
        {"I", "Iodum", 126.90447},
        {"In", "Indium", 114.82},
        {"Ir", "Iridium", 192.22},
        {"K", "Kalium", 39.0983},
        {"Kr", "Krypton", 83.8},
        {"La", "Lanthanum", 138.9055},
        {"Li", "Lithium", 6.941},
        {"Lu", "Lutetium", 174.967},
        {"Mg", "Magnesium", 24.305},
        {"Mn", "Manganum", 54.93805},
        {"Mo", "Molybdenum", 95.94},
        {"N", "Nitrogenium", 14.00674},
        {"Na", "Natrium", 22.989768},
        {"Nb", "Niobium", 92.90638},
        {"Nd", "Neodymium", 144.24},
        {"Ne", "Neon", 20.1797},
        {"Ni", "Niccelium", 58.69},
        {"Np", "Neptunium", 237.0482},
        {"O", "Oxygenium", 15.9994},
        {"Os", "Osmium", 190.2},
        {"P", "Phosphorus", 30.973762},
        {"Pa", "Protactinium", 231.0359},
        {"Pb", "Plumbum", 207.2},
        {"Pd", "Palladium", 106.42},
        {"Pm", "Promethium", 146.9151},
        {"Po", "Polonium", 208.9824},
        {"Pr", "Praseodymium", 140.90765},
        {"Pt", "Platinum", 195.08},
        {"Pu", "Plutonium", 244.0642},
        {"Ra", "Radium", 226.0254},
        {"Rb", "Rubidium", 85.4678},
        {"Re", "Rhenium", 186.207},
        {"Rh", "Rhodium", 102.9055},
        {"Rn", "Radon", 222.0176},
        {"Ru", "Ruthenium", 101.07},
        {"S", "Sulphur", 32.066},
        {"Sb", "Stibium", 121.75},
        {"Sc", "Scandium", 44.95591},
        {"Se", "Selenium", 78.96},
        {"Si", "Silicium", 28.0855},
        {"Sm", "Samarium", 150.36},
        {"Sn", "Stannum", 118.71},
        {"Sr", "Strontium", 87.62},
        {"Ta", "Tantalum", 180.9479},
        {"Tb", "Terbium", 158.92534},
        {"Tc", "Technetium", 98.9063},
        {"Te", "Tellurium", 127.6},
        {"Th", "Thorium", 232.0381},
        {"Ti", "Titanium", 47.88},
        {"Tl", "Thallium", 204.3833},
        {"Tm", "Thulium", 168.93421},
        {"U", "Uranium", 238.0289},
        {"V", "Vanadium", 50.9415},
        {"W", "Wolframium", 183.85},
        {"Xe", "Xenon", 131.29},
        {"Y", "Yttrium", 88.90585},
        {"Yb", "Ytterbium", 173.04},
        {"Zn", "Zincum", 65.39},
        {"Zr", "Zirkonium", 91.224}
    };

    struct FormulaItem {
        string elementSymbol;
        double mass;
        int indexSum;
    };

    std::map<string, FormulaItem> formulaTable;

    std::vector<struct FormulaItem> parseElements(FormulaParser* inputParser);
    string analytics();
    string finalFormula();

private:

};

#endif /* FORMULASCHEMA_H */

