#include "MainWindow.h"
#include <iostream>
#include <filesystem>
#include <fstream>

//Constructor
MainWindow::MainWindow(TDT4102::Point position, TDT4102::Point opplosning, const std::string& title):
AnimationWindow{position.x, position.y, opplosning.x , opplosning.y , title},
quitBtn(TDT4102::Point{QbtnX, QbtnY}, btnWidth, btnHeight, "Quit"),
fileInput(TDT4102::Point{FinpX, FinpY}, FbtnWidth, btnHeight, "CSV file path"),
loadBtn(TDT4102::Point{LbtnX, LbtnY}, btnWidth, btnHeight, "Load"),
dummyArgument{0},
punkter(PunktListe(opplosning))
{   
	add(quitBtn);
    quitBtn.setCallback(std::bind(&MainWindow::cb_quit, this));

    add(fileInput);
    add(loadBtn);
    loadBtn.setCallback(std::bind(&MainWindow::cb_loadBtn, this));
}

//Quit button code
void MainWindow::cb_quit(){
	close();
}

//Load button code
void MainWindow::cb_loadBtn() {
    std::filesystem::path filsti = fileInput.getText();
    std::ifstream inputStream{filsti};
    data.emplace_back(std::make_unique<Data>(punkter , filsti));
}

// Functions
void MainWindow::drawAxes(){
        //Akser for plot 1
        draw_line(punkter.bottom1 , punkter.bottomEnd1);
        draw_line(punkter.bottom1 , punkter.top1);
    
        //Akser for plot 2
        draw_line(punkter.origo2 , punkter.end2);
        draw_line(punkter.bottom2 , punkter.top2);
}
void MainWindow::plot(){
    //Plott 1

    //Plott 2
    unsigned int pikselLengde = punkter.end2.x - punkter.origo2.x;
    unsigned int dx = data[0]->getIndexIntervall(pikselLengde);
    std::vector<int> Y = data[0]->getKanal(1 , data[0]->getKanalForhold(1)[0]);

    for(auto i = 0 ; i < pikselLengde - 1 ; i++){
        TDT4102::Point a = {punkter.origo2.x + i , punkter.origo2.y - Y[i * dx]};
        TDT4102::Point b = {punkter.origo2.x + i + 1 , punkter.origo2.y - Y[(i + 1) * dx]};
        draw_line(a,b);
    }
}
void MainWindow::drawNumber(double number, TDT4102::Point position){
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << number;
    draw_text(position, std::to_string(number), TDT4102::Color::black);
}
void MainWindow::runGraphics(){
    drawAxes();
    if(data.size() != 0){
        if(data[0]->klar){
            plot();
        }    
    }
        
}
