#include "MainWindow.h"
#include <iostream>
#include <filesystem>
#include <fstream>

//Constructor
MainWindow::MainWindow(TDT4102::Point position, TDT4102::Point opplosning, const std::string& title):
AnimationWindow{position.x, position.y, opplosning.x , opplosning.y , title},
dummyArgument{0},
punkter(PunktOppslag(opplosning))
{   
    state = 0;
    layoutvalue = 0;
}

//Quit button code
void MainWindow::cb_quit(){
	close();
}

//Load button code
void MainWindow::cb_loadBtn() {
    //std::filesystem::path filsti = fileInput.getText();
    //std::ifstream inputStream{filsti};
    //data.emplace_back(std::make_unique<Data>(punkter , filsti));
}

//Plotting
void MainWindow::drawAxes(){

}
void MainWindow::plottKanal(unsigned int kanal){

}
void MainWindow::drawNumber(double number, TDT4102::Point position){
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << number;
    draw_text(position, std::to_string(number), TDT4102::Color::black);
}

//Statemaskin
void MainWindow::layout(){
    draw_rectangle(TDT4102::Point{0,0} , punkter.opplosning.x , punkter.opplosning.y , TDT4102::Color::khaki);
    
}
void MainWindow::drawButton(TDT4102::Point TL ,TDT4102::Point BR , std::string tekst ){
    int dx = BR.x-TL.x;
    int dy = BR.y-TL.y;
    draw_image(TL , bilder.button , dx , dy);
    draw_text(TL , tekst , TDT4102::Color() , 30);
    return;
}
bool MainWindow::checkInBetween(TDT4102::Point TL , TDT4102::Point BR , TDT4102::Point check){
    if(check.x > TL.x && check.x < BR.x && check.y < BR.y && check.y > TL.y ){
        return true;
    }
    else{return false;}
}
void MainWindow::meny(){
    bool buttonOnePressed = false;
    bool buttonTwoPressed = false;
    bool buttonThreePressed = false;
    bool buttonFourPressed = false;

    std::vector<PunktOppslag::Meny::Button> knappkoordinater = punkter.meny.knapper;
    std::vector<std::string> navn = {"QUIT" , "LAYOUT" , "PLOTTING" , "FILTER MODE"};

    int antallKnapper = 4;
    draw_image(TDT4102::Point{0,0} , bilder.meny , punkter.opplosning.x , punkter.opplosning.y);

    for(auto i = 0 ; i < antallKnapper ; i++){
        TDT4102::Point TL = knappkoordinater[i].topLeft;
        TDT4102::Point BR = knappkoordinater[i].bottomRight;
        TDT4102::Point mus = TDT4102::AnimationWindow::get_mouse_coordinates();
        if(checkInBetween(TL , BR , mus)){
            draw_rectangle(TDT4102::Point{TL.x-5 , TL.y-5} , BR.x-TL.x + 10 , BR.y-TL.y +10 , TDT4102::Color::white_smoke , TDT4102::Color::black);
        }
        drawButton(knappkoordinater[i].topLeft , knappkoordinater[i].bottomRight , navn[i]);
    }

    TDT4102::Point mus = TDT4102::AnimationWindow::get_mouse_coordinates();
    if(checkInBetween(knappkoordinater[0].topLeft , knappkoordinater[0].bottomRight , mus) && TDT4102::AnimationWindow::is_left_mouse_button_down()){
        close();
    }
    if(checkInBetween(knappkoordinater[1].topLeft , knappkoordinater[1].bottomRight , mus) && TDT4102::AnimationWindow::is_left_mouse_button_down()){
        state = 1;
    }

}
void MainWindow::runGraphics(){
    switch(state)
    {
        case(0):
        {
            meny();
            break;
        }
        case(1):
        {
            layout();
            break;
        }
        case(2):
        {
            break;
        }
        case(3):
        {
            break;
        }
    }       
}
