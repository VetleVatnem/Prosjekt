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

/*---------------------------------DATA----------------------------------*/
/*------------------------------Konstruktører------------------------------*/

Data::Data(PunktListe punkter , std::filesystem::path filsti):
punkter(punkter),
filsti(filsti)
{
    lesCSV();
    //fourierTransform();
};

/*------------------------Funksjoner som tilhører structs----------------*/

void Data::Tid::skaler(Data& skall){
    unsigned int lengdeX = skall.punkter.origo2.x - skall.punkter.end2.x;
}
void Data::Kanal::skaler(Data& skall , const double& forhold){

}
void Data::Transform::skaler(Data& skall , const double& forholdAmp , const double& forholdFase){
    
}

/*-----------------------------HJELPE FUNKSJONER-------------------------*/

void Data::fyllKanal(Kanal& kanal){
    double max = std::round(*max_element(kanal.verdier.begin() , kanal.verdier.end()));
    double min = std::abs(std::round(*min_element(kanal.verdier.begin() , kanal.verdier.end())));
    if(max > min){kanal.konstanter.maksAmplitude = max;}
    else{kanal.konstanter.maksAmplitude = min;}
    kanal.konstanter.forhold = punkter.origo2.y/kanal.konstanter.maksAmplitude;
    kanal.konstanter.antallVerdier = kanal.verdier.size();
    //kanal.skaler(kanal.konstanter.forhold);
}
std::vector<double> Data::konverterTilVektor(const std::string& linje){
    std::vector<double> rad;
    std::stringstream ss(linje);
    std::string tall;

    while (std::getline(ss, tall, ',')){
        try{
            rad.push_back(std::stod(tall));
        }
        catch(const std::invalid_argument&){
            rad.clear();
            break;
        }
    }
    return rad;
}


/*-----------------------------PRIVATE FUNKSJONER------------------------*/

void Data::lesCSV(){
    std::string linje;
    std::vector<double> rad;
    std::ifstream inputstream{filsti};
    int kolonner;

    if(filsti.extension() != ".csv"){
        std::cout << "Filen er ikke en .csv fil." << std::endl;
        return;
    }
    else if(!inputstream){
        std::cout << "Kunne ikke opne filen" << std::endl;
        return;
    }

    while(std::getline(inputstream, linje)){
        kolonner = konverterTilVektor(linje).size();
        if(kolonner)
        {
            break;
        }
    }

    switch (kolonner)
    {
        case 2:{
            tid = std::make_unique<Data::Tid>();
            En = std::make_unique<Data::Kanal>();
            FEn = std::make_unique<Data::Transform>();
            unsigned int antallrader = 1;

            while(std::getline(inputstream , linje)){
                rad = konverterTilVektor(linje);
                
                if(rad.size() != 2){
                    std::cout << "Filen mangler verdier på rad " << antallrader << std::endl;
                }
                else{
                    tid->verdier.push_back(rad[0]);
                    En->verdier.push_back(rad[1]);
                }
                antallrader += 1;
            }
            break;
        }
        case 3:{
            tid = std::make_unique<Data::Tid>();
            En = std::make_unique<Data::Kanal>();
            To = std::make_unique<Data::Kanal>();
            FEn = std::make_unique<Data::Transform>();
            FTo = std::make_unique<Data::Transform>();
            unsigned int antallrader = 1;

            while(std::getline(inputstream , linje)){
                rad = konverterTilVektor(linje);
                
                if(rad.size() != 3){
                    std::cout << "Filen mangler verdier på rad " << antallrader << std::endl;
                }
                else{
                    tid->verdier.push_back(rad[0]);
                    En->verdier.push_back(rad[1]);
                    To->verdier.push_back(rad[2]);   
                }
                antallrader += 1;
            }
            break;
        }
        default:{
            std::cout << "Ugyldig antall kolonner i CSV filen" << std::endl;
            break;
        }
    }
    
    if(tid != nullptr){
        tid->konstanter.AntallSamples = tid->verdier.size();
        double dt = tid->verdier[2]-tid->verdier[1];
        for (auto i = 0; i < tid->konstanter.AntallSamples ; i++){
                tid->verdier[i] = i*dt;
        }
        tid->konstanter.sampleFrekvens = 1/dt;
        tid->konstanter.tidsIntervall = tid->verdier[tid->konstanter.AntallSamples - 1];
        tid->skaler();
    }else{throw std::runtime_error("Tidsvektoren ble ikke initialisert!");}
    
    if(En != nullptr){
        fyllKanal(*En);
    }else{throw std::runtime_error("Kanal 1 ble ikke initialisert!");}

    if(To != nullptr && kolonner == 3){
        fyllKanal(*To);
    }else if(To == nullptr && kolonner == 3){throw std::runtime_error("Kanal 2 ble ikke initialisert!");}
}

/*-----------------------------PUBLIC FUNKSJONER-------------------------*/
const std::vector<double>& Data::getTid() const{
    return this->tid->verdier;
}
const std::vector<double>& Data::getKanal(int channel) const{
    if(channel == 1){
        return this->En->verdier;
    }
    else{
        return this->To->verdier;
    }
}
