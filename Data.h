#pragma once

#include "Fourier.h"
#include <AnimationWindow.h>
#include <fstream>

struct PunktListe{
    TDT4102::Point opplosning;
    TDT4102::Point origo1;
    TDT4102::Point origo2;
    TDT4102::Point end1;
    TDT4102::Point end2;
    TDT4102::Point top1;
    TDT4102::Point top2;
    TDT4102::Point bottom1;
    TDT4102::Point bottom2;
    TDT4102::Point bottomEnd1;
    TDT4102::Point bottomEnd2;

    PunktListe();
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

            std::vector<double> verdier;
            std::vector<unsigned int> skaleringIndexIntervaller;
            std::vector<unsigned int> horisontalPiklser;
            std::vector<std::vector<double>> skalerte;
            Konstanter konstanter;

            void skaler(unsigned int lengdeX);
        };
        
        struct Kanal{
            struct Konstanter{
                double maksAmplitude;
                double antallVerdier;
                std::vector<double> forhold;
                double yAkseTopp;
                double yAkseBunn;
            };

            std::vector<double> verdier;
            std::vector<std::vector<int>> skalerte;
            Konstanter konstanter;

            void skaler(double forhold);
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

            std::vector<std::complex<double>> fourierTransform;
            std::vector<double> amplitudeSpekter;
            std::vector<double> faseSpekter;
            std::vector<int> skalertAmplitudeSpekter;
            std::vector<int> skalertFaseSpekter;
            Max max;
            Min min;
            Forhold forhold;

            void skaler(double forholdAmp ,double forholdFase);
        };

        //Filstier og filnavn
        std::filesystem::path filsti;

        //Punkter på skjermen
        PunktListe punkter;

        //Data beholdere
        std::unique_ptr<Data::Tid> tid;
        std::vector<std::unique_ptr<Data::Kanal>> kanaler;
        std::vector<std::unique_ptr<Data::Transform>> transformer;
        
        //funksjoner som kun skal brukes av klassen
        void lesCSV();
        void fourierTransform();

        //Hjelpe funksjoner
        void fyllKanal(Kanal& kanal);
        std::vector<double> konverterTilVektor(const std::string& linje);

    public:
        //Konstruktør
        Data(const PunktListe punkter , std::filesystem::path filsti);
        Data() = default;

        // Tillat flytting
        Data(Data&&) noexcept = default;
        Data& operator=(Data&&) noexcept = default;
    
        //Fjerne kopi
        Data(const Data&) = delete;
        Data& operator=(const Data&) = delete;

        //Verdier
        bool klar = false;

        //Hente ut skalerings verdier
        const std::filesystem::path getFilsti();
        const std::vector<double>& getKanalForhold(unsigned int kanal);
        const std::vector<int>& getKanal(const unsigned int& kanal , double forhold);
        const std::vector<double>& getTid(const unsigned int& lengdeX);
        const unsigned int getIndexIntervall(const unsigned int& lengdeX);

        //Funksjoner for å skrive data
        void skrivCSV(std::filesystem::path mappe , std::string navn);
};

