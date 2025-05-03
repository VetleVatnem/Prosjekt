#pragma once

#include "Data.h"
#include <windows.h>
#include "AnimationWindow.h"
#include "widgets/Button.h"
#include "widgets/TextInput.h"
#include "widgets/DropdownList.h"
#include "Fourier.h"


class MainWindow : public TDT4102::AnimationWindow{
private:

    PunktOppslag punkter;

    //Plotting
    void drawNumber(double number, TDT4102::Point position);
    void drawAxes();
    void plottKanal(unsigned int kanal);

    //Meny
    unsigned int state;
    unsigned int layoutvalue;
    bool checkInBetween(TDT4102::Point TL , TDT4102::Point BR , TDT4102::Point check);
    void drawButton(TDT4102::Point TL , TDT4102::Point BR , std::string tekst);
    void meny();
    void layout();
    Bilder bilder;
    
    
public:

	void cb_quit();

    std::vector<std::unique_ptr<Data>> data;
    void cb_loadBtn();

    //Functions
    void runGraphics();
    
    //Constructor
    MainWindow(TDT4102::Point position, TDT4102::Point opplosning , const std::string& title);
    int dummyArgument;
};