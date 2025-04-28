#include "MainWindow.h"
#include <iostream>
#include <filesystem>
#include <fstream>

//Constructor
MainWindow::MainWindow(TDT4102::Point position, int width, int height, const std::string& title):
AnimationWindow{position.x, position.y, width, height, title},
quitBtn(TDT4102::Point{QbtnX, QbtnY}, btnWidth, btnHeight, "Quit"),
fileInput(TDT4102::Point{FinpX, FinpY}, FbtnWidth, btnHeight, "CSV file path"),
loadBtn(TDT4102::Point{LbtnX, LbtnY}, btnWidth, btnHeight, "Load"),
minLim(TDT4102::Point{mininpX, mininpY}, FbtnWidth, btnHeight, "Min. freq."),
maxLim(TDT4102::Point{maxinpX, maxinpY}, FbtnWidth, btnHeight, "Max. freq."),
channelChoice(TDT4102::Point{ddlPosX, ddlPosY}, FbtnWidth, btnHeight, valg),
dummyArgument{0},
width(width),
height(height)
{   
	add(quitBtn);
    quitBtn.setCallback(std::bind(&MainWindow::cb_quit, this));

    add(fileInput);
    add(loadBtn);
    loadBtn.setCallback(std::bind(&MainWindow::cb_loadBtn, this));

    add(minLim);
    add(maxLim);
    add(channelChoice);
}

//Quit button code
void MainWindow::cb_quit(){
	close();
}

//Load button code
void MainWindow::cb_loadBtn() {
    std::ifstream inputStream{fileInput.getText()};
    for (auto i = valg.size() - 1 ; i > 0 ; i -= 1){
        valg.pop_back();
    }
    //Testverdier implementert
    maxFrekvens = static_cast<double>(std::stod(maxLim.getText()));
    minFrekvens = static_cast<double>(std::stod(minLim.getText()));

    if (!inputStream) { // Sjekker om strømmen ble åpnet
        std::cout << "Could not open file" << std::endl;
        return;
    }
    readCSV(inputStream);
    Matrix<std::complex<double>> transformMatrise = DFT(time.size());
    fourierCoeffisients = transformMatrise * channel1;
    
    if (time.size() > 1){
        scaleTime();
    }
    if (channel1.size() > 1){
        scaleChannel(1);
        valg[0] = std::string("Kanal 1");
    }
    if (channel2.size() > 1){
        scaleChannel(2);
        valg.push_back(std::string("Kanal 2"));
    }
    if(valg.size() >= 2){
        valg.push_back(std::string("Begge"));
    }
    channelChoice.setOptions(valg);
}

// Functions
void MainWindow::readCSV(std::ifstream& inputStream) {
    std::string line;
    std::vector<int> row; //endret for å minske minnebruk pga reallokering i while løkken...
    row.reserve(3);

    int validlines = 0;
    while (std::getline(inputStream, line)) {
        std::stringstream ss(line);
        std::string cell;
        row.clear(); //rensker vektoren for hver iterasjon

        while (std::getline(ss, cell, ',')) {
            try {
                row.push_back(std::stod(cell)); 
            } 
            catch (const std::invalid_argument&) {
                row.clear();
                break;
            }
        }
        if (row.size() >= 2) {
            validlines++;
        }
    }


    //reserves places for the vectors
    time.resize(validlines , 0);
    channel1.resize(validlines , 0);
    channel2.resize(validlines , 0);
    
    //reset inputstream
    inputStream.clear();
    inputStream.seekg(0, std::ios::beg);

    //fills the vectors
    int i = 0;
    while (std::getline(inputStream, line)) {
        std::stringstream ss(line);
        std::string cell;
        std::vector<double> row;

        while (std::getline(ss, cell, ',')){
            try{
                row.push_back(std::stod(cell));
            }
            catch(const std::invalid_argument&){
                row.clear();
                break;
            }
        }

        if (row.size() >= 2) {
            time[i] = row[0];      
            channel1[i] = (row[1]);  
            if (row.size() == 3) {            
                channel2[i] = (row[2]);
            }
            i++;
        }
    }


    //normalices time
    if (time[0] != 0){
        double dt = time[2]-time[1];
        for (auto i = 0; i < time.size() ; i++){
               time[i] = i*dt;
        }
    } 

    N = channel1.size();
    sampleFrekvens = N/time[N-1];
}
const std::vector<double>& MainWindow::getTime() const {
    return time;
}
const std::vector<double>& MainWindow::getChannel1() const {
    return channel1;
}
const std::vector<double>& MainWindow::getChannel2() const {
    return channel2;
}
const std::vector<std::complex<double>>& MainWindow::getFourierCoeffisients() const{
    return fourierCoeffisients;
}
void MainWindow::fourierTransform(){
    int N = time.size();
    auto transformMatrise = DFT(N);
    fourierCoeffisients = std::move(transformMatrise * channel1);
}
void MainWindow::drawAxes(){
        //Akser for plot 1
        TDT4102::Point BLP1{300 , 1300};
        TDT4102::Point BRP1{2260 , 1300};
        TDT4102::Point TLP1{300 , 840};
        draw_line(BLP1 , BRP1);
        draw_line(BLP1 , TLP1);
    
        for (auto i = 1 ; i < 70 ; i++){
            TDT4102::Point a{300 + i * 28 , 1295};
            TDT4102::Point b{300 + i * 28 , 1305};
            draw_line(a , b);
        }
    
    
        //Akser for plot 2
        TDT4102::Point MLP2{300 , 370};
        TDT4102::Point MRP2{2260 , 370};
        TDT4102::Point TLP2{300 , 140};
        TDT4102::Point BLP2{300 , 600};
        draw_line(MLP2 , MRP2);
        draw_line(BLP2 , TLP2);
    
        for (auto i = 1 ; i < 70 ; i++){
            TDT4102::Point a{300 + i * 28 , 365};
            TDT4102::Point b{300 + i * 28 , 375};
            draw_line(a , b);
        }
}
void MainWindow::plot(){
    //Plott 2
    std::string choice = channelChoice.getSelectedValue();
    if(choice == std::string("Kanal 1")){
        for (auto i = 0 ; i < scaledTimeVector.size() - 1; i ++){
            TDT4102::Point a{300 + i , 370 - (scaledChannel1Vector[i])};
            TDT4102::Point b{300 + i + 1 , 370 - (scaledChannel1Vector[i + 1])};
            draw_line(a , b);
        }
        double maxElementChannel1 = *max_element(channel1.begin(), channel1.end());
        double minElementChannel1 = *min_element(channel1.begin(), channel1.end());
        drawNumber(maxElementChannel1 , TDT4102::Point{300, 120});
        drawNumber(minElementChannel1 , TDT4102::Point{300,600});
    } 
    else if(choice == std::string("Kanal 2")){
        for (auto i = 0 ; i < scaledTimeVector.size() - 1; i ++){
            TDT4102::Point a{300 + i , 370 - (scaledChannel2Vector[i])};
            TDT4102::Point b{300 + i + 1 , 370 - (scaledChannel2Vector[i + 1])};
            draw_line(a , b);
        }
        double maxElementChannel2 = *max_element(channel2.begin(), channel2.end());
        double minElementChannel2 = *min_element(channel2.begin(), channel2.end());
        drawNumber(maxElementChannel2 , TDT4102::Point{300, 120});
        drawNumber(minElementChannel2 , TDT4102::Point{300,600});
    } 
    else if (choice == std::string("Begge")){
        for (auto i = 0 ; i < scaledTimeVector.size() - 1; i ++){
            TDT4102::Point a{300 + i , 370 - (scaledChannel1Vector[i])};
            TDT4102::Point b{300 + i + 1 , 370 - (scaledChannel1Vector[i + 1])};
            draw_line(a , b);

            TDT4102::Point c{300 + i , 370 - (scaledChannel2Vector[i])};
            TDT4102::Point d{300 + i + 1 , 370 - (scaledChannel2Vector[i + 1])};
            draw_line(c , d);
        }
        double maxElementChannel1 = *max_element(channel1.begin(), channel1.end());
        double minElementChannel1 = *min_element(channel1.begin(), channel1.end());
        double maxElementChannel2 = *max_element(channel2.begin(), channel2.end());
        double minElementChannel2 = *min_element(channel2.begin(), channel2.end());
        if(maxElementChannel1 > maxElementChannel2){
            drawNumber(maxElementChannel1 , TDT4102::Point{300, 120});
            drawNumber(minElementChannel1 , TDT4102::Point{300,600});
        }
        else{
            drawNumber(maxElementChannel2 , TDT4102::Point{300, 120});
            drawNumber(minElementChannel2 , TDT4102::Point{300,600});
        }
    }  
    drawNumber(time[scaledTimeIndexVector.size() - 1], TDT4102::Point{2300,370});


    //Plott 1
    scaleFourierCoeffisient();
    if(scaledAmplitudeVector.size() > 1){
        for (auto i = 0 ; i < scaledAmplitudeVector.size() - 1 ; i++){
            TDT4102::Point a{300 + (i * fourierCoeffisientsIndexIntervall) , 1300 - scaledAmplitudeVector[i]};
            TDT4102::Point b{300 + ((i+1) * fourierCoeffisientsIndexIntervall) , 1300 - scaledAmplitudeVector[i+1]};
            draw_line(a , b);
        }
    }
    drawNumber(maxAmp , TDT4102::Point{300 , 800});
    drawNumber(minFrekvens, TDT4102::Point{230,1300});
    drawNumber(maxFrekvens, TDT4102::Point{2220,1300});
    drawNumber((maxAmpIndeks/(static_cast<double>(N)))*sampleFrekvens, TDT4102::Point{300 + fourierCoeffisientsIndexIntervall*maxAmpIndeks - kmin*fourierCoeffisientsIndexIntervall , 1310});

}
void MainWindow::scaleTime(){
    unsigned int xLength = 1960;
    std::vector<double> dummyvector = time;
    unsigned int heltallIntervall;

    if(scaledTimeVector.size() != 0){
        scaledTimeVector.clear();
        scaledTimeIndexVector.clear();
    }

    while (xLength % dummyvector.size() != 0) { 
        dummyvector.pop_back();
    }
    heltallIntervall = xLength / dummyvector.size();

    for (auto i = 0; i < dummyvector.size(); i += heltallIntervall) {
        scaledTimeVector.push_back(dummyvector[i]);
        scaledTimeIndexVector.push_back(i);
    }
}
void MainWindow::scaleChannel(int channel){
    switch(channel){
        case(1):{
            if (scaledChannel1Vector.size() != 0){
                scaledChannel1Vector.clear();
            }
            scaledChannel1Vector.reserve(scaledTimeIndexVector.size());
            channel1Max = *max_element(channel1.begin() , channel1.end());
            channel1Min = *min_element(channel1.begin() , channel1.end());
            forholdKanal1 = 230.0 / channel1Max;
            double forhold;
            if (channel1Max > channel2Max){
                forhold = forholdKanal1;
            }
            for (auto i = 0 ; i < scaledTimeIndexVector.size() ; i++){
                double verdi = forhold * channel1[scaledTimeIndexVector[i]];
                int verdiUtenDesimal = static_cast<int>(verdi);
                double diff = verdi - verdiUtenDesimal;
                if(diff >= 0.5){
                    double justertVerdi = verdi + (1.0 - diff);
                    int plotteVerdi = static_cast<int>(justertVerdi);
                    scaledChannel1Vector.push_back(plotteVerdi);
                }
                else{
                    scaledChannel1Vector.push_back(verdiUtenDesimal);
                }
            }
            return;
        }
        case(2):{
            if (scaledChannel2Vector.size() != 0){
                scaledChannel2Vector.clear();
            }
            scaledChannel2Vector.reserve(scaledTimeIndexVector.size());
            channel2Max = *max_element(channel2.begin() , channel2.end());
            channel2Min = *min_element(channel2.begin() , channel2.end());
            forholdKanal2 = 230.0 / channel2Max;
            double forhold;
            if (channel2Max > channel1Max){
                forhold = forholdKanal2;
            }
            for (auto i = 0 ; i < scaledTimeIndexVector.size() ; i++){
                double verdi = forhold * channel2[scaledTimeIndexVector[i]];
                int verdiUtenDesimal = static_cast<int>(verdi);
                double diff = verdi - verdiUtenDesimal;
                if(diff >= 0.5){
                    double justertVerdi = verdi + (1.0 - diff);
                    int plotteVerdi = static_cast<int>(justertVerdi);
                    scaledChannel2Vector.push_back(plotteVerdi);
                }
                else{
                    scaledChannel2Vector.push_back(verdiUtenDesimal);
                }
            }
            return;
        }
    }
}
void MainWindow::scaleFourierCoeffisient(){
    finnVerdierForK();
    scaledAmplitudeVector.clear();
    int intervall = kmax - kmin;
    int xlength = 1960;
    maxAmp = 0;
    maxAmpIndeks = 0;

    for (auto i = kmin ; i <= kmax ; i++) {
        double absValue = std::abs(fourierCoeffisients[i]);
        if (absValue > maxAmp) {
            maxAmp = absValue;
            maxAmpIndeks = i;
        }
    }
    maxAmp = maxAmp*2; //Pga parsevals sats

    if(maxAmp == 0){
        std::cout << "maxAmp i intervallet er 0" << std::endl;
    }
    
    double forhold;
    forhold = 460.0 / maxAmp;
    fourierCoeffisientsIndexIntervall = xlength/intervall;

    for(auto i = kmin ; i <= kmax ; i++){
        double absoluttverdi = forhold * std::abs(fourierCoeffisients[i]) * 2;
        int absIntVerdi = static_cast<int>(absoluttverdi);
        double diff = absoluttverdi - absIntVerdi;

        if (diff >= 0.5 && absoluttverdi > 1e-3){
            double justertVerdi = absoluttverdi + (1.0 - diff);
            int plotteVerdi = static_cast<int>(justertVerdi);
            scaledAmplitudeVector.push_back(plotteVerdi);
        }
        else if (diff < 0.5 && absoluttverdi > 1e-3) {
            scaledAmplitudeVector.push_back(absIntVerdi);
        }
        else{
            scaledAmplitudeVector.push_back(0);
        }
    }
}
void MainWindow::finnVerdierForK(){
    double flytN = static_cast<double>(N);
    double testFrekvens;
    double diff;
    kmin = -1;
    kmax = -1;

    for (auto i = 0 ; i < fourierCoeffisients.size() ; i++){
        testFrekvens = (i/flytN)*sampleFrekvens;
        if ((testFrekvens >= minFrekvens) && (kmin == -1)){
            kmin = i - 1;  
        }
        else if(testFrekvens >= maxFrekvens){
            kmax = i;
            return;
            }
            
    }
    
    std::cout << "Maxfrekvens/minfrekvens out of range" << std::endl;
    return;     
}
void MainWindow::drawNumber(double number, TDT4102::Point position){
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << number;
    draw_text(position, std::to_string(number), TDT4102::Color::black);
}
void MainWindow::setFrekvens(int& frekvens , bool min){
    if (min == true){
        minFrekvens = frekvens;
        return;
    }
    else{
        maxFrekvens = frekvens;
    }
}
const double& MainWindow::getMinFrekvens() const{
    return minFrekvens;
}
const double& MainWindow::getMaxFrekvens() const{
    return maxFrekvens;
}
void MainWindow::scrollFrekvensplott(){
    TDT4102::Point musepeker = TDT4102::AnimationWindow::get_mouse_coordinates();
    TDT4102::Point topLeft{300,840};
    TDT4102::Point bottomRight{2260,1300};

    if( musepeker.x >= topLeft.x &&
        musepeker.x <= bottomRight.x &&
        musepeker.y >= topLeft.y &&
        musepeker.y <= bottomRight.y )
    {
        double hastighet = 0.05;
        if (TDT4102::AnimationWindow::is_right_mouse_button_down()){ //maa legge inn grenser for datasettet slik at den ikke går OOR
            minFrekvens += hastighet;
            maxFrekvens += hastighet;
            return;
        }
        else if (TDT4102::AnimationWindow::is_left_mouse_button_down() && minFrekvens >= 0){
            minFrekvens -= hastighet;
            maxFrekvens -= hastighet;
            return;
        }
    }
    return;
    
}
void MainWindow::zoomFrekvensplott(){
    double zoomHastighet = 0.1;
    TDT4102::Point musepeker = TDT4102::AnimationWindow::get_mouse_coordinates();
    TDT4102::Point topLeft{300,840};
    TDT4102::Point bottomRight{2260,1300};

    if( musepeker.x >= topLeft.x &&
        musepeker.x <= bottomRight.x &&
        musepeker.y >= topLeft.y &&
        musepeker.y <= bottomRight.y )
    {
        if(TDT4102::AnimationWindow::is_key_down(KeyboardKey::UP)){
            if (minFrekvens >= 5){
                minFrekvens -= zoomHastighet;
                maxFrekvens += zoomHastighet;
                return;
            }
            else if(minFrekvens < 5){
                maxFrekvens += zoomHastighet*2;
                return;
            }
            
        }
        else if(TDT4102::AnimationWindow::is_key_down(KeyboardKey::DOWN)){
            if (minFrekvens >= 5){
                minFrekvens += zoomHastighet;
                maxFrekvens -= zoomHastighet;
                return;
            }
            else if(minFrekvens < 5){
                maxFrekvens -= zoomHastighet*2;
                return;
            }
            
        }
    }
}

