#pragma once

#include <Image.h>
#include <AnimationWindow.h>
#include <fstream>
#include <cmath>
#include <complex>
#include <iostream>

struct Bilder{
    TDT4102::Image meny{"Bilder/Collosseum.jpg"};
    TDT4102::Image button{"Bilder/button.jpg"};
    //TDT4102::Image config1{};
    //TDT4102::Image config2{};
    //TDT4102::Image config3{};
};

struct PunktOppslag{
    struct Config{
        struct Plott{
            TDT4102::Point origo;
            TDT4102::Point bunn;
            TDT4102::Point top;
            TDT4102::Point end;
            TDT4102::Point endBunn;
            TDT4102::Point endTop;
            
            Plott(int nummer);
            void skaler(double faktor);
            
            private:
                void genererPunkt(TDT4102::Point TL , TDT4102::Point BR);
        };
        std::vector<Plott> plott;
        Config(int config , TDT4102::Point opplosning);
    };
    
    struct Meny{
        struct Button{
            TDT4102::Point topLeft;
            TDT4102::Point bottomRight;
            Button(int knapp , TDT4102::Point& opplosning);
        };
        std::vector<Button> knapper;
        Meny(TDT4102::Point& opplosning);
        Meny() = default;
    };
    
    Meny meny;
    std::vector<Config> configs;
    TDT4102::Point opplosning;

    PunktOppslag(TDT4102::Point opplosning);
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

            std::vector<std::complex<double>> verdier;
            std::vector<double> frekvens;
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
        PunktOppslag punkter;

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
        Data(const PunktOppslag& punkter , std::filesystem::path filsti);
        Data() = default;

        //Flytting av eierskap
        Data(Data&&) noexcept = default;
        Data& operator=(Data&&) noexcept = default;
    
        //Hindring av kopi
        Data(const Data&) = delete;
        Data& operator=(const Data&) = delete;

        //Verdier
        bool klar = false;

        //Hente ut skalerings verdier
        const std::filesystem::path getFilsti();
        const std::vector<double>& getKanalForhold(unsigned int kanal);
        const std::vector<int>& getKanal(const unsigned int& kanal , double forhold);
        const unsigned int& getAntallKanaler();
        const std::vector<double>& getTid(const unsigned int& lengdeX);
        const unsigned int getIndexIntervall(const unsigned int& lengdeX);

        //Funksjoner for å skrive data
        void skrivCSV(std::filesystem::path mappe , std::string navn);
};

