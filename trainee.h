//
// Created by Olha Vasylyshyn on 1/31/2021.
//

#ifndef PROGRAM_TRAINEE_H
#define PROGRAM_TRAINEE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include <iterator>
#include <limits>




#define assertm(exp, msg) assert(((void)msg, exp))


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


namespace trainee {
    struct Input {
        std::vector<InputLine> inputLines;
    };

    Description readDescription(std::string fileName);

    Input readInput();

    void writeOutput(std::vector<double> results);


}

#endif //PROGRAM_TRAINEE_H
