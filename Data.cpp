#pragma once

#include <thread>
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
PunktOppslag::PunktOppslag(TDT4102::Point opplosning):
    opplosning{opplosning}
{
    //Lager 3 konfigs med 2 , 3 og 4 plott og en meny
    for(int i = 2 ; i < 5 ; i++){
        configs.push_back(Config(i , this->opplosning));
    }
    meny = Meny(opplosning);   
}
PunktOppslag::Config::Config(int config , TDT4102::Point opplosning){
    double skalarQHd = 4/3.0;
    double skalar4K = 2;
    //Genererer 1080p versjon

    switch(config){
        case(2):{
            for(int i = 0 ; i < 2 ; i++){
                plott.push_back(Plott(i));
            } 
            break;   
        }
        case(3):{
            for(auto i = 2 ; i < 5 ; i++){
                plott.push_back(Plott(i));
            } 
            break;
        }
        case(4):{
            for(auto i = 5 ; i < 9 ; i++){
                plott.push_back(Plott(i));
            }  
            break;
        }
    }

    //skalerer hvis det er 1440 eller 2160.
    switch(opplosning.y){
        case(1440):{
            for(auto i = 0 ; i < config ; i++){
                this->plott[i].skaler(skalarQHd);
            }
            break;
        }
        case(2160):{
            for(auto i = 0 ; i < config ; i++){
                this->plott[i].skaler(skalar4K);
            }
            break;
        }
    }
}
PunktOppslag::Config::Plott::Plott(int nummer){
    switch(nummer){
        case(0):{
            TDT4102::Point TL{0,0};
            TDT4102::Point BR{0,0};
            genererPunkt(TL , BR);
            break;
        }
        case(1):{
            TDT4102::Point TL{0,0};
            TDT4102::Point BR{0,0};
            genererPunkt(TL , BR);
            break;
        }
        case(2):{
            TDT4102::Point TL{0,0};
            TDT4102::Point BR{0,0};
            genererPunkt(TL , BR);
            break;
        }
        case(3):{
            TDT4102::Point TL{0,0};
            TDT4102::Point BR{0,0};
            genererPunkt(TL , BR);
            break;
        }
        case(4):{
            TDT4102::Point TL{0,0};
            TDT4102::Point BR{0,0};
            genererPunkt(TL , BR);
            break;
        }
        case(5):{
            TDT4102::Point TL{0,0};
            TDT4102::Point BR{0,0};
            genererPunkt(TL , BR);
            break;
        }
        case(6):{
            TDT4102::Point TL{0,0};
            TDT4102::Point BR{0,0};
            genererPunkt(TL , BR);
            break;
        }
        case(7):{
            TDT4102::Point TL{0,0};
            TDT4102::Point BR{0,0};
            genererPunkt(TL , BR);
            break;
        }
        case(8):
            TDT4102::Point TL{0,0};
            TDT4102::Point BR{0,0};
            genererPunkt(TL , BR);
            break;
    }
}
PunktOppslag::Meny::Meny(TDT4102::Point& opplosning){
    for(auto i = 0 ; i < 4 ; i++){
        knapper.push_back(Button(i,opplosning));
    }
}
PunktOppslag::Meny::Button::Button(int i , TDT4102::Point& opplosning){
    double skalarQHd = 4/3.0;
    double skalar4K = 2;

    switch(opplosning.y){
        case(1080):{
            int høyde = 50;
            int bredde = 200;
            int avstand = 20;
            topLeft =       { 100 , 100 + i*høyde + i*avstand    };
            bottomRight =   {topLeft.x + bredde , topLeft.y + høyde};
        }

        case(1440):{
            int høyde = static_cast<int>(50*skalarQHd);
            int bredde = static_cast<int>(200*skalarQHd);
            int avstand = static_cast<int>(20*skalarQHd);
            topLeft =       { static_cast<int>(100*skalarQHd) , static_cast<int>(100*skalarQHd) + i*høyde + i*avstand    };
            bottomRight =   {topLeft.x + bredde , topLeft.y + høyde};
        }

        case(2160):{
            int høyde = 50;
            int bredde = 200;
            int avstand = 20;
            topLeft =       { 100 , 100 + i*høyde + i*avstand    };
            bottomRight =   {topLeft.x + bredde , topLeft.y + høyde};
        }
    
    }
}
void PunktOppslag::Config::Plott::genererPunkt(TDT4102::Point TL , TDT4102::Point BR){
    int lengde = BR.y - TL.y;
    top       = TL;
    endBunn   = BR;
    origo     = { TL.x , TL.y + (lengde/2)};
    bunn      = { TL.x , TL.y + lengde};
    end       = { BR.x , BR.y - (lengde/2)};
    endTop   = { BR.x , BR.y - lengde};
}
void PunktOppslag::Config::Plott::skaler(double faktor){
    origo.x     =   static_cast<int>(origo.x*faktor); 
    origo.y     =   static_cast<int>(origo.y*faktor); 
    bunn.x      =   static_cast<int>(bunn.x*faktor);
    bunn.y      =   static_cast<int>(bunn.y*faktor);
    top.x       =   static_cast<int>(top.x*faktor);
    top.y       =   static_cast<int>(top.y*faktor);
    end.x       =   static_cast<int>(end.x*faktor);
    end.y       =   static_cast<int>(end.y*faktor);
    endBunn.x   =   static_cast<int>(endBunn.x*faktor);
    endBunn.y   =   static_cast<int>(endBunn.y*faktor);
    endTop.x    =   static_cast<int>(endTop.x*faktor);
    endTop.y    =   static_cast<int>(endTop.y*faktor);
}

/*---------------------------------DATA----------------------------------*/
/*-----------------------------Konstruktører-----------------------------*/

Data::Data(const PunktOppslag& punkter , std::filesystem::path filsti):
punkter(punkter),
filsti(filsti)
{
    lesCSV();
    fourierTransform();
};

/*------------------------Funksjoner som tilhører structs----------------*/

void Data::Tid::skaler(unsigned int lengdeX){
    try{
        this->horisontalPiklser.push_back(lengdeX);
        std::vector<double> skalert;
        if(lengdeX < this->konstanter.AntallSamples){
            int i = 0;
            while (((this->konstanter.AntallSamples - i) % lengdeX) != 0) {
                i++;
            }
            this->skaleringIndexIntervaller.push_back((this->konstanter.AntallSamples-i) / lengdeX);
            skalert.resize(lengdeX);
            for(auto i = 0 ; i < lengdeX ; i++){
                skalert[i] = this->verdier[i*this->skaleringIndexIntervaller[0]];
            }
            skalerte.push_back(skalert);
            return;
        }
        else{
            throw std::invalid_argument("I objekt Data->Tid, funksjon skaler() er antall piksler (legndeX) større enn antall samples i datasettet.");
        }
    }
    catch(const std::exception& e){std::cerr << "Unntaket er: " << e.what() << std::endl;}
}
void Data::Kanal::skaler(double forhold){
    std::vector<int> skalert;
    skalert.resize(this->konstanter.antallVerdier);

    for(auto i = 0 ; i < skalert.size() ; i++){
        skalert[i] = static_cast<int>(std::round(forhold * this->verdier[i]));
    }

    this->konstanter.forhold.push_back(forhold);
    this->skalerte.push_back(skalert);
    return;
}
void Data::Transform::skaler(double forholdAmp , double forholdFase){
    
}

/*-----------------------------HJELPE FUNKSJONER-------------------------*/

void Data::fyllKanal(Kanal& kanal){
    double max = *max_element(kanal.verdier.begin() , kanal.verdier.end());
    double min = std::abs(*min_element(kanal.verdier.begin() , kanal.verdier.end()));

    if(max > min){kanal.konstanter.maksAmplitude = max;}
    else{kanal.konstanter.maksAmplitude = min;}

    kanal.konstanter.yAkseTopp = std::ceil(kanal.konstanter.maksAmplitude);
    kanal.konstanter.yAkseBunn = -std::ceil(kanal.konstanter.maksAmplitude);
    kanal.konstanter.antallVerdier = kanal.verdier.size();
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

    if(kolonner > 1){
        tid = std::make_unique<Data::Tid>();
        for(auto i = 0 ; i < kolonner-1 ; i++){
            kanaler.push_back(std::make_unique<Data::Kanal>());
            transformer.push_back(std::make_unique<Data::Transform>());
        }
        unsigned int antallrader = 1;

        while(std::getline(inputstream , linje)){
            rad = konverterTilVektor(linje);
            
            if(rad.size() != kolonner){
                std::cout << "Filen mangler verdier på rad " << antallrader << std::endl;
            }
            else{
                tid->verdier.push_back(rad[0]);
                for(auto j = 1 ; j < kolonner ; j++){
                    kanaler[j - 1]->verdier.push_back(rad[j]);
                }
            }
            antallrader += 1;
        }
    }else{throw std::invalid_argument("I klassen Data, funksjonen lesCSV() ble det gitt en tom CSV siden kolonner = 0.");}
    
    if(tid != nullptr){
        tid->konstanter.AntallSamples = tid->verdier.size();
        double dt = tid->verdier[2]-tid->verdier[1];
        for (auto i = 0; i < tid->konstanter.AntallSamples ; i++){
                tid->verdier[i] = i*dt;
        }
        tid->konstanter.sampleFrekvens = 1/dt;
        tid->konstanter.tidsIntervall = tid->verdier[tid->konstanter.AntallSamples - 1];
    }else{throw std::runtime_error("Tidsvektoren ble ikke initialisert!");}
    
    for(auto i = 0 ; i < kanaler.size() ; i++){
        if(kanaler[i] != nullptr){
            fyllKanal(*kanaler[i]);
        }else{throw std::runtime_error("I klassen Data, funksjon lesCSV er en peker i vektoren kanaler en nullptr.");}
    }
    klar = true;
}
void Data::fourierTransform(){
    if(this->kanaler.size() > 0){
        for(auto a = 0 ; a < this->kanaler.size() ; a++){
            std::vector<double> kanal = this->kanaler[a]->verdier;
            double N = static_cast<double>(kanal.size());
            for(auto i = 0 ; i < kanal.size() ; i++){
                std::complex<double> sum = 0;
                for(auto j = 0 ; j < kanal.size() ; j++){
                    sum += exp(std::complex<double>(0 , (- 2 * M_PI * i * j) / N)) * kanal[j];
                }
                this->transformer[a]->verdier.push_back(sum);
                this->transformer[a]->amplitudeSpekter.push_back(std::abs(sum));
                this->transformer[a]->faseSpekter.push_back(std::arg(sum));
                this->transformer[a]->frekvens.push_back((i/N) * this->tid->konstanter.sampleFrekvens);
            }
        }
    }else{throw std::out_of_range("Kanalene ble ikke initialisert. Dermed kan ikke Transformen utfores.");}
        
}

/*-----------------------------PUBLIC FUNKSJONER-------------------------*/
const std::filesystem::path Data::getFilsti(){
    return this->filsti;
}
const std::vector<double>& Data::getKanalForhold(unsigned int kanal){
    if(kanal <= this->kanaler.size()){
        return this->kanaler[kanal-1]->konstanter.forhold;
    }else{throw std::out_of_range("Kanalen eksisterer ikke i Data objektet.");}
}
const std::vector<int>& Data::getKanal(const unsigned int& kanal , double forhold){
    for(auto i = 0 ; i < this->kanaler[kanal-1]->konstanter.forhold.size() ; i++){
        if(std::abs(forhold - this->kanaler[kanal-1]->konstanter.forhold[i]) < 1){
            return this->kanaler[kanal-1]->skalerte[i];
        }
    }
    this->kanaler[kanal - 1]->skaler(forhold);
    if (std::abs(forhold - this->kanaler[kanal - 1]->konstanter.forhold.back()) < 1) {
        return this->kanaler[kanal - 1]->skalerte.back();
    }

    throw std::runtime_error("Ugyldig tilstand: Forhold ikke funnet etter skalering.");
}
const std::vector<double>& Data::getTid(const unsigned int& lengdeX){
    for(auto i = 0 ; i < this->tid->horisontalPiklser.size() ; i++){
        if(lengdeX == this->tid->horisontalPiklser[i]){
            return this->tid->skalerte[i];
        }
    }
    this->tid->skaler(lengdeX);
    return getTid(lengdeX);
}
const unsigned int Data::getIndexIntervall(const unsigned int& lengdeX){
    for(auto i = 0 ; i < this->tid->horisontalPiklser.size() ; i++ ){
        if(lengdeX == this->tid->horisontalPiklser[i]){
            return this->tid->skaleringIndexIntervaller[i];
        }
    }
    this->tid->skaler(lengdeX);
    return getIndexIntervall(lengdeX);
}
const unsigned int& Data::getAntallKanaler(){
    return this->kanaler.size();
}






