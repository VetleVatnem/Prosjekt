#pragma once
#include <Fourier.h>
#include <MainWindow.h>
#include <cmath>



int main()
{   
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
    return 0;
}
