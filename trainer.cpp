//
// Created by Olha Vasylyshyn on 1/31/2021.
//
#include "trainee.h"
#include "trainer.h"

//program -t train_set.txt -i data_in.txt -o data_out.txt < description_in.txt > description_out.txt



using namespace std::regex_constants;

struct Coordinate {
    double x;
    double y;
};

struct TrainSet {
    std::vector<Coordinate> coordinates;
};

struct LearningData {
    const double learninRate = 0.01;
    int iter = 1000;
    const int k = 1;
    std::vector<double> cost= std::vector<double>(iter, 0.0);

};

namespace trainer {
    struct Input {
        int iter;
    };

    Input readInput(std::string fileName) {
        Input in;
        std::ifstream input(fileName);
        std::string line;
        getline(input, line);
        std::smatch m;
        std::regex_search(line, m, std::regex("[[:digit:]]+"));

        in.iter = std::stoi(m.str());
        return in;
    }
}

TrainSet readTrainSet(std::string fileName) {
    TrainSet tempTrainSet;
    std::ifstream input(fileName);
    for ( std::string line; getline(input, line); ) {
        std::istringstream stream(line);
        std::vector<std::string> results(std::istream_iterator<std::string>{stream},
                                         std::istream_iterator<std::string>());
        Coordinate tempCoord;
        assertm(results.size() == 2, "TRAIN SET LINE HAS TO BE 2 NUMBERS!");
        for ( auto s = 0; s < results.size(); s += 2 ) {

            tempCoord.x = atof(results[0].c_str());
            tempCoord.y = atof(results[1].c_str());
        }
        tempTrainSet.coordinates.push_back(tempCoord);
    }
    return tempTrainSet;
}
void writeToFile(std::string filename, std::string text){
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << text<<'\n';
        file.close();
    }

}


Description readDescription() {
    Description tempDesc;
    bool first_red = false;

    for ( std::string line; getline(std::cin, line); ) {
        std::istringstream stream(line);
        std::vector<std::string> results(std::istream_iterator<std::string>{stream},
                                         std::istream_iterator<std::string>());

        if (!first_red) {
            assertm(results.size() == 2, "FIRST DESC LINE HAS TO BE 2 NUMBERS!");
            tempDesc.k = atoi(results[0].c_str());
            tempDesc.n = atoi(results[1].c_str());
            first_red = true;
            continue;
        }

        assertm(results.size() == tempDesc.n + 1, "DescLine error!");
        DescriptionLine tempDescLine;

        for ( auto i = 0; i < results.size() - 1; i++ ) {
            tempDescLine.wspolrzedne.push_back(atoi(results[i].c_str()));
        }
        tempDescLine.wspolczynnik = atof(results[results.size() - 1].c_str());
        tempDesc.descriptionLines.push_back(tempDescLine);
    }
    return tempDesc;
}

namespace trainer {
    std::vector<double> hypothesis(const std::vector<double> &theta, const std::vector<std::vector<double>> &coorX) {
        assertm(theta.size()==coorX[0].size(), "[HYPOTHESIS]SIZE OF AFFAYS IS DIFFERENT!");
        std::vector<double> hypo(coorX.size(), 0.0);
        for ( int i = 0; i < coorX.size(); i++ ) {
            //hypo[i] = 0.0;
            for ( auto j = 0; j < coorX[0].size();j++ ) {
                hypo[i] += theta[j]*coorX[i][j];
            }
        }
        return hypo;
    }

    void gradientDescent(std::vector<double>&theta, LearningData &ld,std::vector<double> hypo,
                         std::vector<std::vector<double>> &coorX,std::vector<double> &coorY, int n){

        for (int i = 0; i < ld.iter; i++){
            theta[0] = theta[0] - (ld.learninRate/coorX.size())*sum(substract(hypo, coorY));

            for (int j = 1; j < n+1; j++){
                theta[j] = theta[j] - (ld.learninRate/coorX.size())*
                        sum(multiply(substract<double>(hypo, coorY),transpose(coorX)[j]));

            }
            hypo = hypothesis(theta,coorX);
            ld.cost[i] = (1.0 / coorX.size()) * 0.5 * sum(power<double>(substract(hypo, coorY),2));

        }

    }
    void linRegression(const TrainSet &t, LearningData &ld,const Description &param){
        std::vector<double> y;
        std::vector<std::vector<double>>x;
        std::vector<double> theta;
        for(short i= 0; i< t.coordinates.size();i++){
            std::vector<double> temp;
            temp.push_back(1.0);
            temp.push_back(t.coordinates[i].x);
            x.push_back(temp);
            y.push_back(t.coordinates[i].y);
        }
        for (auto p : param.descriptionLines){
            theta.push_back(p.wspolczynnik);
        }
        auto hypo = hypothesis(theta,x);
        gradientDescent(theta,ld,hypo,x,y,param.n);
        //std::cout<<theta.size()<<" "<<param.descriptionLines.size();
        std::cout<<param.k<<' '<<param.n<<'\n';
        for(int i = 0; i < theta.size(); i++){
            std::cout << std::setprecision(17)<<param.descriptionLines[i].wspolrzedne[0]<<' '<<theta[theta.size()-1-i]<<"\n";
        }
    }
}





int main(int argc, const char *argv[]) {
    //linux
    //assertm(argc == 7, "Unexpected args! error!");

    std::string trainsetFileName;
    std::string inputFileName;
    std::string outputFileName;
    std::string descriptionFileName;
    for ( int i = 0; i < argc; i++ ) {
        auto arg = std::string(argv[i]);
        if (arg.compare("-t") == 0) {
            trainsetFileName = std::string(argv[i + 1]);
            continue;
        } else if (arg.compare("-i") == 0) {
            inputFileName = std::string(argv[i + 1]);
            continue;
        } else if (arg.compare("-o") == 0) {
            outputFileName = std::string(argv[i + 1]);
            continue;
        }
            //windows
//        else if (arg.compare("-d") == 0) {
//            descriptionFileName = std::string(argv[i + 1]);
//            continue;
//        }
    }

    auto trainSet = readTrainSet(trainsetFileName);
    auto input = trainer::readInput(inputFileName);
//    //windows
//    auto parameters = trainee::readDescription(descriptionFileName);
//    linux
    auto parameters = readDescription();
/*
    for ( auto t: trainSet.coordinates ) {
        std::cout << std::setprecision(16) << t.x << ' ' << t.y << '\n';
    }
    std::cout << input.iter << '\n' << '\n';
    std::cout << parameters.k << ' ' << parameters.n << '\n';
    for ( auto d: parameters.descriptionLines ) {
        for ( auto de: d.wspolrzedne )
            std::cout << de << ' ';
        std::cout << static_cast<double>(d.wspolczynnik) << '\n';
    }
*/

    LearningData learningData;
    trainer::linRegression(trainSet,learningData,parameters);
    writeToFile(outputFileName, "iterations="+std::to_string(learningData.iter));





    return 0;

}

