/* 
 * File:   formulaschema.cpp
 * Author: kuestere
 * 
 * Created on 1. Oktober 2018, 19:28
 */

#include "formulaschema.h"

FormulaSchema::FormulaSchema() {
    for (auto element : elements) {
        FormulaItem formulaItem = {element.symbol, 0.0, 0};
        formulaTable[element.symbol] = formulaItem;
    }
}

FormulaSchema::FormulaSchema(const FormulaSchema& orig) {
}

FormulaSchema::~FormulaSchema() {
}

std::vector<FormulaSchema::FormulaItem> FormulaSchema::parseElements(FormulaParser* inputParser) {
    std::vector<FormulaSchema::FormulaItem> outputElements;
    auto closingBracket = inputParser->scanForOpeningBracket();
    if (closingBracket == 'q') {
        throw(2);
    }
    if (closingBracket != u'?') {
        // found opening bracket
        std::vector<FormulaSchema::FormulaItem> bracketElements;
        do {
            // run through at least once
            auto partialElements = parseElements(inputParser);
            if (partialElements.size() == 0) break;
            for (auto partial : partialElements) {
                bracketElements.push_back(partial);
            }
            if (inputParser->endOfString) {
                switch (closingBracket) {
                    // no closing bracket
                    case ')':
                        throw(6);
                    default:
                        throw(7);
                }
                break;
            }
        } while (!inputParser->isCharClosingBracket(closingBracket));
        // scan for integer index, if no integer found, index is one
        int index = inputParser->scanForIndex();
        if (index < 0) {
            //  index 0 not allowed
            //ErrorAlert(message: 8).show()
            throw(8);
            return {};
        }
        for (auto element : bracketElements) {
            element.indexSum *= index;
            outputElements.push_back(element);
        }
    } else {
        string symbol = inputParser->scanForElement();
        //found an element?
        if (symbol.empty()) {
            throw(2);
            return {};
        }
        // now identify the element symbol
        if (formulaTable.find(symbol) == formulaTable.end()) {
            //no suitable element symbol found
            throw(3);
            return {};
        }
        // scan for integer index, if no integer found, index is one
        int index = inputParser->scanForIndex();
        if (index < 0) {
            //index 0 not allowed
            throw(8);
            return {};
        }
        int indexsum = 1;
        indexsum *= index;
        FormulaItem formulaItem = {symbol, 0.0, indexsum};
        outputElements.push_back(formulaItem);
    }
    // scan for bond sign, result is not evaluated at the moment
    auto bondSign = inputParser->scanForBond();
    if (!bondSign.empty()) {
        //after bound must follow a formula element
        if ((inputParser->followsClosingBracket()) || (inputParser->endOfString)) {
            throw(5);
        }
    }
    return outputElements;
}

string FormulaSchema::analytics() {
    stringstream analyticStream;
    analyticStream << "Elementary Analysis: " << endl;
    for (auto element : elements) {
        auto symbol = element.symbol;
        FormulaItem formulaItem = formulaTable[symbol];
        auto indexSum = formulaItem.indexSum;
        if (indexSum > 0) {
            double percentage = formulaItem.mass / totalMass * 100;
            analyticStream << symbol << "\t"
                << setprecision(3) << fixed << percentage << " %" << endl;
        }
    }
    return analyticStream.str();
}

string FormulaSchema::finalFormula() {
    stringstream formulaStream;
    totalMass = 0.0;
    for (auto element : elements) {
        auto symbol = element.symbol;
        FormulaItem formulaItem = formulaTable[symbol];
        auto indexSum = formulaItem.indexSum;
        if (indexSum > 0) {
            formulaStream << symbol;
            double massMultiple = element.mass;
            if (indexSum > 1) {
                formulaStream << indexSum;
                massMultiple *= indexSum;
            }
            formulaTable[symbol].mass = massMultiple;
            totalMass += massMultiple;
        }
    }
    return formulaStream.str();
}
