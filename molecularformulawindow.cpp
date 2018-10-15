/* 
// File:   molecularformulawindow.cpp
// Author: kuestere
//
//             Molecular Formula
//            Summenformel V 1.4.3
//     Das Programm wurde entwickelt fuer
//  ehemalige Firma Chemische Fabrik Stockhausen
//     GmbH, Krefeld von Dr. E. Kuester 1993
//      zunaechst Kommandozeilenversion
// 15.12.1993 Englische Version mit defines
// 20.03.1995 V 1.3.3  Eingabepuffer größer
// 26.06.1995 V 1.3.31 Puffer noch groesser
//      Version fuer Windows mit Borland-C
// 24.09.1998 V 1.3.4  Edit Controls ohne Dialog
//      Version ohne Stockhausen-Bindung
//  1.03.2006 V 1.3.5 Microsoft Visual C# 2005
//       Kommandozeilenversion in C#
//   portiert auf Apple PC Mac OSX ab 10.6
// 31.01.2012 V 1.3.6 Mono Framework 2.10.88 mit MonoDevelop
//     Kommandozeilenversion in Objective-C
// 10.03.2012 V 1.3.7 mit XCode 4.2.1
//        GUI-Version in Objective-C
//  7.11.2012 V 1.3.8 mit XCode 4.5.1
//  Last revised on 2012-11-07
//        GUI-Version in Swift
// 17.07.2014 V 1.4.0 mit Xcode 6.0 Beta
// 16.09.2014 V 1.4.1 mit XCode 6.0 GM
// 28.12.2015 V 1.4.2 mit XCode 7.2 und Swift 2.1
//        GUI-Version in C++
// 27.09.2018 V 1.4.3 mit Netbeans 8.2, GTK+ mit gtkmm wrapper
//  Created by Erich Kuester, Krefeld, Germany
//    Copyright © 2014 - 2018 Erich Kuester.
//            All rights reserved.
//
// fuer Bindungen: "-" ":" "=" "." "·"
// fuer komplexere Formeln "[" "]" "(" ")"
// fuer Kristallwasser, Eisenheptahydrat = FeSO4.[H2O]7
// 
// Renewed on September 27, 2018 at 18:36
// Last changes on October 5, 2018
 */

#include "molecularformulawindow.h"
#include "about.xpm"

const Glib::ustring app_title = "Gtk+: Chemistry Application - Molecular Formula";

MolecularFormulaWindow::MolecularFormulaWindow(const Glib::RefPtr<Gtk::Application>& app)
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_MenuBar(),
  s_MenuFile(),
  s_MenuItemNew(Gtk::Stock::NEW),
  s_MenuItemQuit(Gtk::Stock::QUIT),
  s_MenuItemAbout(Gtk::Stock::ABOUT),
  s_MenuHelp(),
  m_InputLabel("Formel:"),
  m_FormulaLabel("Summenformel:"),
  m_WeightLabel("Molekulargewicht:"),
  m_TextWindow(),
  m_Dialog()
{
    set_title(app_title);
    set_border_width(5);
    set_default_size(160, 320);
    // add vertical box
    add(m_VBox);
    // menu "File"
    m_MenuFile = Gtk::MenuItem("Datei");
    s_MenuItemNew.signal_activate().connect(sigc::mem_fun(*this,
        &MolecularFormulaWindow::on_file_new));
    s_MenuItemQuit.signal_activate().connect(sigc::mem_fun(*this,
        &MolecularFormulaWindow::on_action_quit));
    s_MenuFile.append(s_MenuItemNew);
    s_MenuFile.append(s_MenuItemQuit);
    m_MenuFile.set_submenu(s_MenuFile);
    // menu "Help"
    m_MenuHelp = Gtk::MenuItem("Hilfe");
    s_MenuItemAbout.signal_activate().connect(sigc::mem_fun(*this,
        &MolecularFormulaWindow::on_help_about));
    s_MenuHelp.append(s_MenuItemAbout);
    m_MenuHelp.set_submenu(s_MenuHelp);
    // set menu bar
    m_MenuBar.append(m_MenuFile);
    m_MenuBar.append(m_MenuHelp);
    m_VBox.pack_start(m_MenuBar, Gtk::PACK_SHRINK);

    // add grid with labels and entries
    m_VBox.pack_start(m_Grid);
    m_Grid.set_border_width(6);
    //Arrange the widgets inside the grid
    m_Grid.set_row_spacing(16);
    m_Grid.set_column_spacing(10);

    m_InputLabel.set_hexpand(true);
    m_InputLabel.set_vexpand(false);
    m_InputLabel.set_halign(Gtk::ALIGN_START); // left justified
    m_Grid.attach(m_InputLabel, 0, 0, 1, 1); // column 0, row 0
    m_Grid.attach(m_InputEntry, 1, 0, 1, 1); // column 1, row 0

    m_FormulaLabel.set_hexpand(true);
    m_FormulaLabel.set_vexpand(false);
    m_FormulaLabel.set_halign(Gtk::ALIGN_START);
    m_Grid.attach(m_FormulaLabel, 0, 1, 1, 1); // column 0, row 1
    m_FormulaEntry.set_editable(false);
    m_Grid.attach(m_FormulaEntry, 1, 1, 1, 1); // column 1, row 1

    m_WeightLabel.set_vexpand(false);
    m_WeightLabel.set_hexpand(true);
    m_WeightLabel.set_halign(Gtk::ALIGN_START);
    m_Grid.attach(m_WeightLabel, 0, 2, 1, 1); // column 0, row 2
    m_WeightEntry.set_editable(false);
    m_Grid.attach(m_WeightEntry, 1, 2, 1, 1); // column 1, row 2

    m_InputEntry.signal_activate().connect(sigc::mem_fun(*this,
        &MolecularFormulaWindow::on_activated));

    //Create the Text Buffer
    m_refTextBuffer = Gtk::TextBuffer::create();
    m_TextView.set_buffer(m_refTextBuffer);
    m_TextView.set_wrap_mode(Gtk::WRAP_WORD);
    //Add the TextView, inside a ScrolledWindow
    m_TextWindow.set_size_request(-1, 112);
    m_TextWindow.add(m_TextView);
    //Only show the scrollbars when they are necessary:
    m_TextWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    m_VBox.pack_start(m_TextWindow, Gtk::PACK_EXPAND_WIDGET);
    m_VBox.set_border_width(6);

    m_Dialog.set_transient_for(*this);
    m_Dialog.set_logo(Gdk::Pixbuf::create_from_xpm_data(about));
    m_Dialog.set_program_name(app_title);
    m_Dialog.set_version("Version 1.4.3");
    m_Dialog.set_copyright("Copyright © 2018 Erich Küster. All rights reserved.");
    m_Dialog.set_comments("Molecular Formula for Chemists");
    std::ifstream licenseFile("LICENSE");
    std::stringstream licenseStream;
    licenseStream << licenseFile.rdbuf();
    m_Dialog.set_license(licenseStream.str());
    std::ifstream commentsFile("COMMENTS");
    std::stringstream commentsStream;
    commentsStream << commentsFile.rdbuf();
    m_Dialog.set_comments(commentsStream.str());

    m_Dialog.set_website("http://www.gtkmm.org");
    m_Dialog.set_website_label("gtkmm Website - C++ Interfaces for GTK+ and GNOME");

    std::vector<Glib::ustring> list_authors;
    list_authors.push_back("Erich Küster, Krefeld/Germany");
    m_Dialog.set_authors(list_authors);

    m_Dialog.signal_response().connect(
            sigc::mem_fun(*this, &MolecularFormulaWindow::on_about_dialog_response));

    show_all_children();
}

MolecularFormulaWindow::MolecularFormulaWindow(const MolecularFormulaWindow& orig) {
}

MolecularFormulaWindow::~MolecularFormulaWindow() {
}

int MolecularFormulaWindow::errorAlert(int messageNumber) {
    Gtk::MessageDialog dialog(*this,
            "Error: Check input",
            false,
            Gtk::MESSAGE_ERROR,
            Gtk::BUTTONS_OK, // Gtk::BUTTONS_OK, Gtk::BUTTONS_NONE,
            true);
    dialog.set_secondary_text(
            m_StatusMessages[messageNumber]);
    return dialog.run();
}

// handles enter pressed
void MolecularFormulaWindow::on_activated() {
    string inputString = m_InputEntry.get_text();
    // check input
    if (inputString.empty()) {
        auto result = errorAlert(1);
    }
    else {
        // erase text buffer
        Gtk::TextBuffer::iterator iter_begin = 
            m_refTextBuffer->get_iter_at_offset(0);
        Gtk::TextBuffer::iterator iter_end = 
            m_refTextBuffer->get_iter_at_offset(m_refTextBuffer->get_char_count());
        m_refTextBuffer->erase(iter_begin, iter_end);
        // begin the formula parsing
        FormulaSchema overallFormula = FormulaSchema();
        FormulaParser* formulaParser = new FormulaParser(inputString);
        std:vector<FormulaSchema::FormulaItem> elementArray;
        do {
            // run through at least once
            try {
                auto partialFormula = overallFormula.parseElements(formulaParser);
                //if (partialFormula.size() == 0) break;
                for (auto partial : partialFormula) {
                    elementArray.push_back(partial);
                }
            }
            catch (const int number) {
                auto result = errorAlert(number);
                break;
            }
        } while (!formulaParser->endOfString);
        for (auto element : elementArray) {
            auto symbol = element.elementSymbol;
            auto index = element.indexSum;
            // fill formula
            overallFormula.formulaTable[symbol].indexSum += index;
        }
        m_FormulaEntry.set_text(overallFormula.finalFormula());
        stringstream totalStream;
        totalStream << setprecision(4) << fixed << overallFormula.totalMass;
        m_WeightEntry.set_text(totalStream.str());
        //output values for elementary analysis
        Gtk::TextBuffer::iterator iter_start = 
            m_refTextBuffer->get_iter_at_offset(m_refTextBuffer->get_char_count());
        auto iter = m_refTextBuffer->insert(iter_start, overallFormula.analytics());
    }
}

void MolecularFormulaWindow::on_file_new() {
    m_InputEntry.set_text(Glib::ustring());
    Gtk::TextBuffer::iterator iter_begin = 
        m_refTextBuffer->get_iter_at_offset(0);
    Gtk::TextBuffer::iterator iter_end = 
        m_refTextBuffer->get_iter_at_offset(m_refTextBuffer->get_char_count());
    m_refTextBuffer->erase(iter_begin, iter_end);
}

void MolecularFormulaWindow::on_action_quit() {
    hide();
}

void MolecularFormulaWindow::on_help_about() {
    m_Dialog.show();
    //bring it to the front, in case it was already shown:
    m_Dialog.present();
}

void MolecularFormulaWindow::on_about_dialog_response(int response_id) {
    switch (response_id) {
        case Gtk::RESPONSE_CLOSE:
        case Gtk::RESPONSE_CANCEL:
        case Gtk::RESPONSE_DELETE_EVENT:
            m_Dialog.hide();
            break;
        default:
            std::cout << "Unexpected response!" << std::endl;
            break;
    }
}
