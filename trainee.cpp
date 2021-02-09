#include "trainee.h"

//program -d description.txt < in.txt > out.txt


namespace trainee {


    Description readDescription(std::string fileName) {
        Description tempDesc;
        bool first_red = false;
        std::ifstream input(fileName);

        for (std::string line; getline(input, line);) {
            std::istringstream stream(line);
            std::vector<std::string> results(std::istream_iterator<std::string>{stream},
                                             std::istream_iterator<std::string>());

            if(!first_red) {
                assertm(results.size() == 2, "FIRST DESC LINE HAS TO BE 2 NUMBERS!");
                tempDesc.n = atoi(results[0].c_str());
                tempDesc.k = atoi(results[1].c_str());
                first_red = true;
                continue;
            }

            assertm(results.size() == tempDesc.k + 1 , "DescLine error!");
            DescriptionLine tempDescLine;

            for (auto i = 0; i < results.size() - 1; i++) {
                tempDescLine.wspolrzedne.push_back(atoi(results[i].c_str()));
            }
            tempDescLine.wspolczynnik = atof(results[results.size() - 1].c_str());
            tempDesc.descriptionLines.push_back(tempDescLine);
        }
        //assertm(tempDesc.descriptionLines.size() == tempDesc.n + 1 , "DescLine error!");
        return tempDesc;
    }

    Input readInput() {
        Input tempInput;
        for (std::string line; getline(std::cin, line);) {
            std::istringstream stream(line);
            std::vector<std::string> results(std::istream_iterator<std::string>{stream},
                                             std::istream_iterator<std::string>());
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
}


