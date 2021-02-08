#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include <iterator>
#include <limits>



#define assertm(exp, msg) assert(((void)msg, exp))

typedef std::numeric_limits< double > dbl;

struct DescriptionLine {
    std::vector<int> wspolrzedne;
    double wspolczynnik;
};

struct Description {
    int k = 0;
    int n = 0;
    std::vector<DescriptionLine> descriptionLines;
};

struct InputLine {
    std::vector<double> wsp;
};

struct Input {
    std::vector<InputLine> inputLines;
};





Description readDescription(std::string fileName) {
    Description tempDesc;
    bool first_red = false;
    std::ifstream input(fileName);

    for( std::string line; getline( input, line ); )
    {
        std::istringstream stream(line);
        std::vector<std::string> results(std::istream_iterator<std::string>{stream},std::istream_iterator<std::string>());

        if(!first_red) {
            assertm(results.size() == 2, "FIRST DESC LINE HAS TO BE 2 NUMBERS!");
            tempDesc.n = atoi(results[0].c_str());
            tempDesc.k = atoi(results[1].c_str());
            first_red = true;
            continue;
        }

        assertm(results.size() == tempDesc.k + 1 , "DescLine error!");
        DescriptionLine tempDescLine;

        for (auto i = 0; i<results.size()-1; i++) {
            tempDescLine.wspolrzedne.push_back(atoi(results[i].c_str()));
        }
        tempDescLine.wspolczynnik = atof(results[results.size()-1].c_str());
        tempDesc.descriptionLines.push_back(tempDescLine);
    }
    return tempDesc;
}

Input readInput() {
    Input tempInput;
    for( std::string line; getline( std::cin, line ); )
    {
        std::istringstream stream(line);
        std::vector<std::string> results(std::istream_iterator<std::string>{stream},std::istream_iterator<std::string>());
        InputLine tempInputLine;
        for (auto s : results) {
            tempInputLine.wsp.push_back(atof(s.c_str()));
        }
        tempInput.inputLines.push_back(tempInputLine);
    }
    return tempInput;
}

void writeOutput(std::vector<double> results) {
    for (auto r : results) {
        std::cout << r << std::endl;
    }
}


int main(int argc, const char * argv[]) {

    std::cout.precision(dbl::max_digits10);

    assertm(argc == 3, "Unexpected args! error!");
    std::string descriptionFileName;

    for (int i = 0 ; i < argc; i++) {
        auto arg = std::string(argv[i]);
        if(arg.compare("-d") == 0) { descriptionFileName = std::string(argv[i+1]); continue; }
    }

    auto description = readDescription(descriptionFileName);
    auto input = readInput();
    auto result = std::vector<double>();

    auto out = std::vector<double>();
    

    for(int i = 0; i < input.inputLines.size();i++){
        assertm(input.inputLines[i].wsp.size() == description.n , "DescLine n error!");

        result.push_back(0.0);
        result[i] = 0.0;
        for(int j = 0; j < description.descriptionLines.size(); j++){
            double poly = description.descriptionLines[j].wspolczynnik;
            for(int l = 0; l < description.descriptionLines[j].wspolrzedne.size(); l++)
            {
                int iter = description.descriptionLines[j].wspolrzedne[l]-1;
                if(iter > -1)
                {
                    poly *= input.inputLines[i].wsp[iter];
                }
            }
            result[i] += poly;
        }
    }
    writeOutput(result);

}