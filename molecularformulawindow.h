/* 
 * File:   molecularformulawindow.h
 * Author: kuestere
 *
 * Created on 27. September 2018, 18:36
 */

#ifndef MOLECULARFORMULARWINDOW_H
#define MOLECULARFORMULARWINDOW_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <gtkmm.h>
#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
#include <sstream>
#include <string>
#include "formulaparser.h"
#include "formulaschema.h"

using namespace std;

class FormulaParser;
class FormulaSchema;

class MolecularFormulaWindow : public Gtk::Window {
public:
    MolecularFormulaWindow(const Glib::RefPtr<Gtk::Application>& app);
    MolecularFormulaWindow(const MolecularFormulaWindow& orig);
    virtual ~MolecularFormulaWindow();

private:

protected:
    std::vector<Glib::ustring> m_StatusMessages = {
        "Place holder, no error",
        "No formula entered",
        "Element symbol expected",
        "No valid element symbol (actual not in table)",
        "Too many bond signs",
        "Bond sign misplaced here",
        "Closing ) missing",
        "Closing ] missing",
        "Index 0 not allowed",
        "Molecular weight is too big"
    };
    int errorAlert(int messageNumber);

    //Signal handlers for menu
    void on_file_new();
    void on_action_quit();
    void on_help_about();
    //Signal handlers for entries and buttons
    void on_activated();
    //Signal handler for AboutDialog
    void on_about_dialog_response(int response_id);

    //Child widgets:
    Gtk::Box m_VBox;
    Gtk::MenuBar m_MenuBar;
    Gtk::MenuItem m_MenuFile;
    Gtk::Menu s_MenuFile;
    Gtk::ImageMenuItem s_MenuItemNew;
    Gtk::ImageMenuItem s_MenuItemQuit;
    Gtk::MenuItem m_MenuHelp;
    Gtk::Menu s_MenuHelp;
    Gtk::ImageMenuItem s_MenuItemAbout;

    Gtk::Grid m_Grid;

    Gtk::Label m_InputLabel;
    Gtk::Entry m_InputEntry;

    Gtk::Label m_FormulaLabel;
    Gtk::Entry m_FormulaEntry;

    Gtk::Label m_WeightLabel;
    Gtk::Entry m_WeightEntry;

    Gtk::ScrolledWindow m_TextWindow;
    Gtk::TextView m_TextView;
    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

    Gtk::AboutDialog m_Dialog;
};

#endif /* MOLECULARFORMULARWINDOW_H */

