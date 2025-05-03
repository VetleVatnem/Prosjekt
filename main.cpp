#pragma once
#include <Fourier.h>
#include <MainWindow.h>
#include <cmath>

int main()
{   
    /*
    PunktListe punkter(TDT4102::Point{1920,1080});
    Data data;
    if (true){
        data = Data(punkter , "C:\\Users\\vetle\\Documents\\Math4C\\CSVTestFiles\\TestCSV_10Hz_4kHz_Klippetsinus.csv");
    }
    
    std::cout << data.getTid(1480).size() << std::endl;
    std::cout << data.getKanal(1 , 240).size() << std::endl;
    */
    
    MainWindow A(TDT4102::Point(1280,0) , TDT4102::Point(2560,1440) , "DFT");
    while(!A.should_close()) {
        A.runGraphics();
        A.next_frame();
    }
    return 0;
}
