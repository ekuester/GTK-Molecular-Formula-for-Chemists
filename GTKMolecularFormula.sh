g++ `pkg-config gtkmm-3.0 --cflags --libs` -c main.cpp formulaparser.cpp formulaschema.cpp molecularformulawindow.cpp
g++ main.o formulaparser.o formulaschema.o molecularformulawindow.o -o GTKMolecularFormula `pkg-config gtkmm-3.0 --cflags --libs`
./GTKMolecularFormula

