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
    PunktListe punkter;
    void drawNumber(double number, TDT4102::Point position);
    void drawAxes();
    void plot();
    void scrollFrekvensplott();
    void zoomFrekvensplott();
    
public:
    //Window values
    static constexpr int x = 0;
    static constexpr int y = 0;

    //Quit button values
    static constexpr int btnWidth = 70;
    static constexpr int btnHeight = 30;
    int QbtnX = punkter.opplosning.x - btnWidth;
    static constexpr int QbtnY = 0;
    TDT4102::Button quitBtn;
	void cb_quit();

    //File input values
    static constexpr int FbtnWidth = 200;
    static constexpr int FinpX = 0;
    static constexpr int FinpY = 0;
    TDT4102::TextInput fileInput;

    //Load button values
    static constexpr int LbtnX = 0;
    static constexpr int LbtnY = 30 + btnHeight*3; 
    TDT4102::Button loadBtn;
    std::vector<std::unique_ptr<Data>> data;
    void cb_loadBtn();

    //Functions
    void runGraphics();
    
    //Constructor
    MainWindow(TDT4102::Point position, TDT4102::Point opplosning , const std::string& title);
    int dummyArgument;
};