#pragma once
#include <Fourier.h>
#include <MainWindow.h>
#include <cmath>



int main()
{   
    //hjemme = (1290,0 : 2560,1440), Bærbar = (0,0 : 1920,1080)
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
    //test


    /*
    std::vector<std::complex<double>> fouriercoeff = A.getFourierCoeffisients();
    
    unsigned int k = 50; //endre på denne for å skrive ut amplituden til en annen frekvens med formel som er angitt
    unsigned int Sf = A.getTime().size()/A.getTime()[A.getTime().size()-1]; //Samplefrekvens i Hz 
    
    std::cout << "Samplefrekvens[Hz]: " << Sf << std::endl;
    std::cout << "Indeks[k]: " << k << std::endl;
    std::cout << "Frekvens[Hz]: " << (k * Sf)/static_cast<double>(fouriercoeff.size()) << std::endl; 
    std::cout << "Amplitude: " << 2*std::abs(fouriercoeff[k]) << std::endl;
    */
    
    return 0;
}
