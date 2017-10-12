#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <sys/stat.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>

using namespace boost::multiprecision;
using namespace boost::random;


/**
 * Checks for file existence
 */
inline bool file_exits(const std::string& name)
{
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

/************************************************************/
/* Complex type                                             */
/************************************************************/

struct complex_struct {
    cpp_int real; // real part
    cpp_int imaginary; // imaginary part
};

typedef struct complex_struct complex;

/************************************************************/
/* Prototypes                                               */
/************************************************************/

// Complex four-multiply (four real multiplies)
//   a, b - number to multiply
//   z - return value (product)
//void cmul4(complex a, complex b, complex *z);

// Complex three-multiply (three real multiplies)
//   a, b - number to multiply
//   z - return value (product)
complex cmul3(complex x, complex y){
    complex z;
    cpp_int t = (x.real + x.imaginary) * (y.real + y.imaginary);
    cpp_int r = x.real * y.real;
    cpp_int s = x.imaginary * y.imaginary;

    z.real = r - s;
    z.imaginary = t - r - s;
    return z;
}

// Complex list multiply using complex four-multiply
//   u - array of complex
//   first - index of first element to multiply
//   last - index of last element to multiply
//   z - return value, product of u[first..last]
//void cmul4_list(complex *u, int first, int last, complex *z);

// Complex list multiply using complex three-multiply
//   u, first, last, z - same as for cmul4_list()
//void cmul3_list(complex *u, int first, int last, complex *z);

/************************************************************/
/* Main Program                                             */
/************************************************************/

void printComplex(complex a){
    std::cout << "(" << a.real << ", "<< a.imaginary << ")" << std::endl;
}

/**
 * Read numbers from file
 * @param filepath
 * @param numbers
 */
void ReadListOfNumbers(const std::string filepath, std::vector<complex> *numbers){
    //Placeholder std::string
    std::string line;

    //File reader
    std::ifstream file(filepath.c_str());

    //Read from file
    if(!file.is_open()) return;

    //Read line-by-line
    while (getline(file, line)) {
        std::regex reg("[\\(\\),]");
        line = std::regex_replace(line, reg, "");

        //Split the line on spaces
        std::istringstream df(line);

        //Offset substring by one word
        cpp_int real;
        cpp_int imaginary;
        df >> real >> imaginary;

        complex a;
        a.real = real;
        a.imaginary = imaginary;
        numbers->push_back(a);
    }
}

int main(int argc, char *argv[]) {
    std::vector<complex> *numbers = new std::vector<complex>();

    //Check for amount of arguments
    if(argc < 2)
    {
        std::cout << "usage: <program> 8bit.txt" << std::endl;
        return 1;
    }
    //Check if file actually exists
    else if(!file_exits(argv[1]))
    {
        std::cout << "Please give a valid input file (" << argv[1] << ")" << std::endl;
        return 1;
    }

    ReadListOfNumbers(std::string(argv[1]), numbers);

    clock_t t0, t;             // used for timing functions

    t0 = clock();
    //cmul4_list(v, 0, n-1, &z);
    t = clock() - t0;

    std::cout << "*** CMUL4 List ***" << std::endl;
    std::cout << "time: " << ((double) t)/CLOCKS_PER_SEC << std::endl;

    // Time call to cmul3_list()

    t0 = clock();
    complex answer = (*numbers)[0];

    for(unsigned int i = 1; i < numbers->size(); i++){
        answer = cmul3(answer, (*numbers)[i]);
    }
    t = clock() - t0;

    std::cout << "*** CMUL3 List ***" << std::endl;
    std::cout << "time: " << ((double) t)/CLOCKS_PER_SEC << std::endl;
    printComplex(answer);

    delete numbers;
    return 0;
}

/************************************************************/
/* Function Implementations                                 */
/************************************************************/

//
// TO BE WRITTEN: cmul4(), cmul3(), cmul4_list(), cmul3_list(),
//                code to read data file
//
