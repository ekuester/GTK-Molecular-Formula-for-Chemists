# GTK-Molecular-Formula-for-Chemists

Calculation of the molecular formula and the molecular weight, amount of the contained elements in percent is given ( C++ / Linux / Gnome / GTK / gtkmm / chemistry)

This program is accompanying my life since years, I wrote it first in BASIC, followed by versions in Borland Turbo C and Microsoft Visual C# 2005 (both for Windows), switched to Objective C and Swift on Apple Macs and now finally in C++ with use of gtkmm wrapper for Gnome GTK environment of Linux.

The development environment in the moment is Netbeans IDE 8.2 under Fedora 28 Cinnamon. Alternatively you can easily compile and run the program in Terminal with the added shell script:

$ sh ./GTKMolecularFormula.sh

Since I switched from macOS to Fedora Linux (for what reasons ever) I had to change my programming language. For "simplicity" I choose C++ and to my pleasure found its "way to think" very similar to Swift and Objective-C. In some aspects I found C++ in combination with GTK easier compared to Swift ... Furthermore with the gtkmm wrapper you have an excellent tool for developing own programs.

I wrote this program to become familiar with the C++ language, especially the GTK-API under the gtkmm wrapper and to get a feeling how to display different widgets on the screen. Take it as example for handling of windows, menus, labels, entries and textviews.

Usage: You will find the program mostly self explaining. Input your formula into the topmost field, what you can do in a relatively comfortable way by grouping the formula into formula elements. Formula elements means the combination of an element symbol with an index. The only restriction is that indices can only be set behind the formula element which shall be counted. Then let the program do the necessary calculations for you. 

- use the normal element symbols
- use arabic numberals as indices
- use bonds:&nbsp; `-  :  =  .  · ` (only illustrative, not controlled on correctness)
- use paired brackets and/or parenthesis for more complex formulas:&nbsp; `[  ]  (  )`

examples:<br/>
```
organic:
CH2=CH-CO-ONa              2-Propenoic acid, sodium salt (Sodium acrylate)
(CH2=CH-CO)2O              2-Propenoic acid, anhydride (Acrylic anhydride)
CH2=C(CH3)-CO-NH2          2-Methyl-2-propenamide (Methacrylamide)
HO-CO-CH(OH)-CH(OH)-CO-OH  2,3-Dihydroxybutanedioic acid (Tartaric acid)
HOCH2-CO-(CHOH)3-CH2OH     Pentahydroxyhexan-2-one (Fructose)
C6H6                       Benzene
C10H8                      Naphthalene
C4H4C(CH2)CC4H4            Bicyclo[4.4.1]undeca-1,3,5,7,9-pentaene (1,6-Methano[10]annulene)
HO-C17H22(CH3)2-CH(CH3)-(CH2)3-CH(CH3)2
                           (3ß)-cholest-5-en-3-ol (Cholesterol)
inorganic:
[Cu(NH3)4(H2O)]SO4         Tetraamminecopper(II)sulfate, monohydrate
FeSO4·[H2O]7               Iron(II)sulfate, heptahydrate (containing crystallisation water)
 note: FeSO4·7[H2O] is not recognized correctly
```
Pressing the ENTER key will output the overall molecular formula strictly sorted in alphabetical order, the overall molecular mass and the amount of each element in the molecule in percent.

For further explanations look at<br/>
&nbsp;<https://en.wikipedia.org/wiki/Chemical_formula#Molecular_formula><br/>
&nbsp;<https://en.wikipedia.org/wiki/Molecular_mass><br/>

Disclaimer: Use the program for what purpose you like, but hold in mind, that I will not be responsible for any harm it will cause to your hard- or software. It was your decision to use this piece of software.

