#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include <iterator>

#define assertm(exp, msg) assert(((void)msg, exp))



struct SetLine {
    std::vector<double > approxPoints;
    double expectedOut = 0.0;
};

struct Set {
    std::vector<SetLine > set;
    int n =0;
};
struct InLine {
    std::vector<double> wsp;
};
struct In {
    std::vector<InLine> trainedPoly;
};





Set readSet(std::string fileName) {
    Set tempSet;
    std::ifstream input(fileName);

    for( std::string line; getline( input, line ); )
    {
        std::istringstream stream(line);
        std::vector<std::string> results(std::istream_iterator<std::string>{stream},
                                         std::istream_iterator<std::string>());

        SetLine tempSetLine;
        for (auto i = 0; i<results.size()-1; i++) {
            tempSetLine.approxPoints.push_back(atof(results[i].c_str()));

        }
        tempSetLine.expectedOut = atof(results[results.size()-1].c_str());
        tempSet.set.push_back(tempSetLine);

    }
    return tempSet;
}

In readInput() {
    In tempIn;
    for( std::string line; getline( std::cin, line ); )
    {
        std::istringstream stream(line);
        std::vector<std::string> results(std::istream_iterator<std::string>{stream},std::istream_iterator<std::string>());
        InLine tempInLine;
        for (auto s : results) {
            tempInLine.wsp.push_back(atof(s.c_str()));
        }
        tempIn.trainedPoly.push_back(tempInLine);

    }
    return tempIn;
}

void writeOutput(std::vector<double> results) {
    for (auto r : results) {
        std::cout << r << std::endl;
    }
}


int main(int argc, const char * argv[]) {
    //assertm(argc == 3, "Unexpected args! error!");
    std::string setFileName;

    for (int i = 0 ; i < argc; i++) {
        auto arg = std::string(argv[i]);
        if(arg.compare("-t") == 0) { setFileName = std::string(argv[i+1]); continue; }
    }
    std::cout<<setFileName<< '\n';

    auto set = readSet(setFileName);
    auto input = readInput();
    auto result = std::vector<double>();

    std::cout << set.n << std::endl;
    for (auto s : set.set){
        for (auto i : s.approxPoints){
            std::cout << i << ' ';
        }
        std::cout << "expected"<< s.expectedOut << std::endl;
    }
    std::cout << "-----------------" << std::endl;
    for (auto in : input.trainedPoly){
        for (auto t : in.wsp){
            std::cout << t << ' ';
        }
        std::cout <<"\n";
    }



    // writeOutput(result);

}