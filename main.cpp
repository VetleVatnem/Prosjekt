#pragma once
#include <Fourier.h>
#include <MainWindow.h>
#include <cmath>

int main()
{   
    PunktListe punkter(TDT4102::Point{1920,1080});
    Data A(punkter , "C:\\Users\\vetle\\Documents\\Math4C\\CSVTestFiles\\TestCSV_10Hz_4kHz_Klippetsinus.csv");
    std::cout << A.getTid()[400] << std::endl;
    std::cout << A.getKanal(1)[0] << std::endl;
    /*
    MainWindow A(TDT4102::Point(1290,0) , 2560 , 1440 , "DFT");
    while(!A.should_close()) {
        A.drawAxes();
        A.scrollFrekvensplott();
        A.zoomFrekvensplott();
        if(A.getTime().size() > 0){
            A.plot();
        }
        A.next_frame();
    }
    */
    return 0;
}
