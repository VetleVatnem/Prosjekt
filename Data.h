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
        //Strukturdefinisjoner med data som hører sammen
        struct Tid{
            struct Konstanter{
                int AntallSamples;
                double sampleFrekvens;
                double tidsIntervall;
            };

            Data* skallklasse;
            std::vector<double> verdier;
            int skaleringIndexIntervall;
            std::vector<int> skalert;
            Konstanter konstanter;

            void skaler();
        };
        
        struct Kanal{
            struct Konstanter{
                double maksAmplitude;
                double antallVerdier;
                double forhold;
            };

            Data* skallklasse;
            std::vector<double> verdier;
            std::vector<int> skalerteVerdier;
            Konstanter konstanter;

            void skaler(double& forhold);
        };

        struct Transform{
            //Verdier
            struct Max{
                double AmplitudeFrekvens;
                int AmplitideIndeks;
                double FaseFrekvens;
                int FaseIndeks;
            };

            struct Min{
                double nullFaseFrekvens;
                int nullFaseIndeks;
                double minFaseFrekvens;
                int minFaseIndeks;
            };

            struct Forhold{
                double amplitudePlott;
                double fasePlott;
            };

            Data* skallklasse;
            std::vector<std::complex<double>> fourierTransform;
            std::vector<double> amplitudeSpekter;
            std::vector<double> faseSpekter;
            std::vector<int> skalertAmplitudeSpekter;
            std::vector<int> skalertFaseSpekter;
            Max max;
            Min min;
            Forhold forhold;

            void skaler(const double& forholdAmp ,const double& forholdFase);
        };

        //Data beholdere
        std::unique_ptr<Data::Tid> tid;
        std::unique_ptr<Data::Kanal> En;
        std::unique_ptr<Data::Kanal> To;
        std::unique_ptr<Data::Transform> FEn;
        std::unique_ptr<Data::Transform> FTo;
    
        //Filstier og filnavn
        std::filesystem::path filsti;

        //Punkter på skjermen
        PunktListe punkter;

        //funksjoner som kun skal brukes av klassen
        void lesCSV();
        void fourierTransform();
        void skaler();

        //Hjelpe funksjoner
        void fyllKanal(Kanal& kanal);
        std::vector<double> konverterTilVektor(const std::string& linje);

    public:
        //Konstruktør
        Data(PunktListe punkter , std::filesystem::path filsti);

        //funksjoner for å hente ut data og opplysninger
        const std::vector<double>& getTid() const;
        const std::vector<double>& getKanal(int channel) const;
        const std::vector<std::complex<double>>& getFourierTransform(int channel) const;
        const int& getSkalertTid() const;
        const std::vector<int>& getSkalertKanal(int channel) const;
        const std::vector<int>& getSkalertAmplitude(int channel) const;
        const std::vector<int>& getSkalertFase(int channel) const;
        const int& getIndexLav() const;
        const int& getIndexHoy() const;
        double findMaxAbs(const int& start , const int& end) const;
        
        //Funksjoner for å endre data
        void setLowIndex(int& low);
        void setHighIndex(int& high);
        void setFrekvensMin(double& low);
        void setFrekvensHoy(double& high);
        void scaleFourier(const int& kanal);

        //Funksjoner for å skrive data
        void skrivCSV(std::filesystem::path mappe , std::string navn);
};

