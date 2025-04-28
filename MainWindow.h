#pragma once

//#include <algorithm>
#include "AnimationWindow.h"
#include "widgets/Button.h"
#include "widgets/TextInput.h"
#include "widgets/DropdownList.h"
#include "Fourier.h"


class MainWindow : public TDT4102::AnimationWindow{
private:
    int width;
    int height;

    std::vector<double> time;
    std::vector<double> channel1;
    std::vector<double> channel2;
    std::vector<std::complex<double>> fourierCoeffisients;
    
    double sampleFrekvens;
    int N;
    int kmin;
    int kmax;
    double maxAmp;
    int maxAmpIndeks;

    //Frekvenser som skal vises
    double maxFrekvens;
    double minFrekvens; 

    //Skalerte vektorer
    std::vector<double> scaledTimeVector;
    std::vector<int> scaledTimeIndexVector;
    std::vector<int> scaledChannel1Vector;
    std::vector<int> scaledChannel2Vector;
    std::vector<int> scaledAmplitudeVector;
    int fourierCoeffisientsIndexIntervall;

    //Skalerings variabler
    double forholdKanal1;
    double forholdKanal2;
    double channel1Max;
    double channel1Min;
    double channel2Max;
    double channel2Min;

    //priv funksjoner
    void scaleTime();
    void scaleChannel(int channel);
    void scaleFourierCoeffisient();
    void finnVerdierForK();
    void drawNumber(double number, TDT4102::Point position);
    
public:
    //Window values
    static constexpr int x = 0;
    static constexpr int y = 0;

    //Quit button values
    static constexpr int btnWidth = 70;
    static constexpr int btnHeight = 30;
    int QbtnX = width - btnWidth;
    static constexpr int QbtnY = 0;
    TDT4102::Button quitBtn;
	void cb_quit();

    //File input values
    static constexpr int FbtnWidth = 200;
    static constexpr int FinpX = 0;
    static constexpr int FinpY = 0;
    TDT4102::TextInput fileInput;

    //Load button values
    static constexpr int LbtnX = 0;
    static constexpr int LbtnY = 30 + btnHeight*3; 
    TDT4102::Button loadBtn;
    void cb_loadBtn();

    //min lim input values
    static constexpr int mininpX = 0;
    static constexpr int mininpY = 10 + btnHeight;
    TDT4102::TextInput minLim;

    //max lim input values
    static constexpr int maxinpX = 210;
    static constexpr int maxinpY = 10 + btnHeight;
    TDT4102::TextInput maxLim;

    //Dropdownlist values
    static constexpr int ddlPosX = 0 ;
    static constexpr int ddlPosY = 20 + btnHeight*2;
    std::vector<std::string> valg{""};
    TDT4102::DropdownList channelChoice;

    //Functions
    void readCSV(std::ifstream& inputStream);
    const std::vector<double>& getTime() const;
    const std::vector<double>& getChannel1() const;
    const std::vector<double>& getChannel2() const;
    const std::vector<std::complex<double>>& getFourierCoeffisients() const; 
    void fourierTransform();
    void drawAxes();
    void plot();
    void setFrekvens(int& frekvens , bool min);
    const double& getMinFrekvens() const;
    const double& getMaxFrekvens() const;
    void scrollFrekvensplott();
    void zoomFrekvensplott();
    

    //Constructor
    MainWindow(TDT4102::Point position, int width, int height, const std::string& title);
    int dummyArgument;
};