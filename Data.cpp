#pragma once

#include "Data.h"
/*
    origo1{460 , 1070},
    origo2{460 , 350},
    end1{2460 , 1070},
    end2{2460 , 350},
    top1{460 , 740},
    top2{460 , 20},
    bottom1{460 , 1400},
    bottom2{460 , 680}
*/
PunktListe::PunktListe(TDT4102::Point opplosning):
    opplosning{opplosning}
{
    double skalarQHd = 4/3.0;
    double skalar4K = 2;
    switch(opplosning.x){
        case(1080):{
            int X1 = static_cast<int>((0.125*opplosning.x + 100));
            int Y1 = static_cast<int>((0.75*opplosning.y));
            int Y2 = static_cast<int>((0.25*opplosning.y));
            int X2 = static_cast<int>((opplosning.x - 100));
            int amp = 250;

            origo1  =   { X1 , Y1 };
            origo2  =   { X1 , Y2 };
            top1    =   { X1 , Y1 - amp };
            bottom1 =   { X1 , Y1 + amp };
            top2    =   { X1 , Y2 - amp };
            bottom2 =   { X1 , Y2 + amp };
            end1    =   { X2 , Y1 };
            end2    =   { X2 , Y2 };
        }
        case(1440):{
            int X1 = static_cast<int>((0.125*opplosning.x + 100)*skalarQHd);
            int Y1 = static_cast<int>((0.75*opplosning.y)*skalarQHd);
            int Y2 = static_cast<int>((0.25*opplosning.y)*skalarQHd);
            int X2 = static_cast<int>((opplosning.x - 100)*skalarQHd);
            int amp = static_cast<int>(250*skalarQHd);

            origo1  =   { X1 , Y1 };
            origo2  =   { X1 , Y2 };
            top1    =   { X1 , Y1 - amp };
            bottom1 =   { X1 , Y1 + amp };
            top2    =   { X1 , Y2 - amp };
            bottom2 =   { X1 , Y2 + amp };
            end1    =   { X2 , Y1 };
            end2    =   { X2 , Y2 };
        }
        case(2160):{
            int X1 = static_cast<int>((0.125*opplosning.x + 100)*skalar4K);
            int Y1 = static_cast<int>((0.75*opplosning.y)*skalar4K);
            int Y2 = static_cast<int>((0.25*opplosning.y)*skalar4K);
            int X2 = static_cast<int>((opplosning.x - 100)*skalar4K);
            int amp = static_cast<int>(250*skalar4K);

            origo1  =   { X1 , Y1 };
            origo2  =   { X1 , Y2 };
            top1    =   { X1 , Y1 - amp };
            bottom1 =   { X1 , Y1 + amp };
            top2    =   { X1 , Y2 - amp };
            bottom2 =   { X1 , Y2 + amp };
            end1    =   { X2 , Y1 };
            end2    =   { X2 , Y2 };
        }
    }
}

/*------------------------------Konstruktør------------------------------*/
Data::Data(PunktListe punkter , std::filesystem::path filsti):
punkter(punkter),
filsti(filsti)
{
    lesCSV();
    fourierTransform();
    skaler();
};
/*-----------------------------PRIVATE FUNKSJONER------------------------*/

void Data::lesCSV(){
    std::string linje;
    int rader;
    int kolonner;
    std::ifstream inputstream{filsti};

    if(filsti.extension() != ".csv"){
        std::cout << "Filen er ikke en .csv fil." << std::endl;
        return;
    }
    else if(!inputstream){
        std::cout << "Kunne ikke opne filen" << std::endl;
        return;
    }

    while (std::getline(inputstream, linje)) {
        std::stringstream ss(linje);
        std::string tall;
        std::vector<double> rad;

        while (std::getline(ss, tall, ',')){
            try{
                rad.push_back(std::stod(tall));
            }
            catch(const std::invalid_argument&){
                rad.clear();
                break;
            }
        }
        if(antallKanaler == 0){
            antallKanaler = rad.size() - 1;
        }

        if (rad.size() >= 2) {
            tid.push_back(rad[0]);      
            kanal1.push_back(rad[1]) ;
            if (antallKanaler == 2) {            
                kanal2.push_back(rad[2]);
            };
        }
    }

    double dt = tid[2] - tid[1];
    sampleFrekvens = 1/dt;
    antallSamples = tid.size();
    
    for (auto i = 0 ; i < tid.size() ; i++){
        tid[i] = i*dt;
    }
    double posamp = *max_element(kanal1.begin() , kanal1.end());
    double negamp = std::abs(*min_element(kanal1.begin() , kanal1.end()));
    if (posamp > negamp){ amplitudeKanal1 = posamp; }
    else { amplitudeKanal1 = negamp; }
    
    if(antallKanaler == 2){
        posamp = *max_element(kanal2.begin() , kanal2.end());
        negamp = std::abs(*max_element(kanal2.begin() , kanal2.end()));
        if(posamp > negamp){ amplitudeKanal2 = posamp ; }
        else{ amplitudeKanal2 = negamp ; }
    }
    //lesCSV skal bruke punktene som funksjonen genererPunkt()

}




