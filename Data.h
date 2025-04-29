#pragma once

#include "Fourier.h"
#include <AnimationWindow.h>
#include <fstream>

class PunktListe{
    public:
        TDT4102::Point opplosning;
        TDT4102::Point origo1;
        TDT4102::Point origo2;
        TDT4102::Point end1;
        TDT4102::Point end2;
        TDT4102::Point top1;
        TDT4102::Point top2;
        TDT4102::Point bottom1;
        TDT4102::Point bottom2;
    PunktListe(TDT4102::Point opplosning);
};

class Data{
    private:
        //Nyttige verdier til datasettet : Hentet fra lesCSV() fil
        unsigned int antallKanaler; 
        unsigned int amplitudeKanal1; 
        unsigned int amplitudeKanal2;
        unsigned int sampleFrekvens;
        unsigned int antallSamples;

        //Verdier for oppløsning og skalering
            //Skaleringsverdier
            double forholdSignal;
            double forholdFourier;
            unsigned int indeksLow;
            unsigned int indeksHigh;
            double frekvensMin;
            double frekvensHøy;
            PunktListe punkter;
            

        //Datasett og skalerte versjoner av dem
        std::vector<double> tid;
        std::vector<double> kanal1;
        std::vector<double> kanal2;
        std::vector<std::complex<double>> fourierTransform1;
        std::vector<std::complex<double>> fourierTransform2;
        std::vector<int> skalertTidIndex;
        std::vector<int> skalertTid;
        std::vector<int> skalertKanal1;
        std::vector<int> skalertKanal2;
        std::vector<int> skalertAmplitude1;
        std::vector<int> skalertAmplitude2;
        std::vector<int> skalertFase1;
        std::vector<int> skalertFase2;
        
        //Filstier og filnavn
        std::filesystem::path filsti;

        //funksjoner som kun skal brukes av klassen
        void lesCSV();
        void fourierTransform();
        void genererPunkt();
        void skaler();
    
    public:
        //Konstruktør
        Data(PunktListe punkter , std::filesystem::path filsti);

        //funksjoner for å hente ut data
        const std::vector<double>& getkanal(int channel) const;
        const std::vector<std::complex<double>>& getFourierTransform(int channel) const;
        const std::vector<int>& getSkalertKanal(int channel) const;
        const std::vector<int>& getSkalertAmplitude(int channel) const;
        const std::vector<int>& getSkalertFase(int channel) const;
        const int& getIndexLav() const;
        const int& getIndexHoy() const;
        
        //Funksjoner for å endre data
        void setLowIndex(int& low);
        void setHighIndex(int& high);
        void setFrekvensMin(double& low);
        void setFrekvensHoy(double& high);

        //Funksjoner for å skrive data
        void skrivCSV(std::filesystem::path mappe , std::string navn);
};

