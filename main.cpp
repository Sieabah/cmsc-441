/**
Contributors:
	Christopher Sidell (csidell1@umbc.edu)
	Joshua Standiford (jstand1@umbc.edu)
*/

#include <cstdio>
#include <ctime>
#include <cmath>

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

/************************************************************
 * Complex type                                             *
 ************************************************************/

struct complex_struct {
    cpp_int real; // real part
    cpp_int imaginary; // imaginary part
};

typedef struct complex_struct complex;

/**
 * Complex four-multiply (four real multiplies)
 * @param x operand one
 * @param y operand two
 * @return
 */
complex cmul4(complex z1, complex z2){
    complex z;

    cpp_int r = (z1.real * z2.real - z1.imaginary * z2.imaginary);
    cpp_int i = (z1.real * z2.imaginary + z1.imaginary * z2.real);

    z.real = r;
    z.imaginary = i;

    return z;
}

/**
 * Recursively multiplies (4 real multiplication)
 * @param numbers array to complex numbers to be multiplied
 * @param u recursive multiplied complex number
 * @param index current index in vector
 * @return
 */
complex cmul4_list(std::vector<complex> *numbers, complex u, int index, int limit){
    index++;
    if(index < limit){
        u = cmul4_list(numbers, cmul4(u, (*numbers)[index]), index, limit);
    }
    return u;
}


/**
 * Complex three-multiply (three real multiplies)
 * @param x operand one
 * @param y operand two
 * @return
 */
complex cmul3(complex x, complex y){
    complex z;
    cpp_int t = (x.real + x.imaginary) * (y.real + y.imaginary);
    cpp_int r = x.real * y.real;
    cpp_int s = x.imaginary * y.imaginary;

    z.real = r - s;
    z.imaginary = t - r - s;
    return z;
}

/**
 * Recursively multiplies (3 real multiplication)
 * @param numbers array to complex numbers to be multiplied
 * @param u recursive multiplied complex number
 * @param index current index in vector
 * @param limit size of divide-and-conquer limit
 * @return
 */
complex cmul3_list(std::vector<complex> *numbers,  complex u, int index, int limit){
    index++;
    if(index < limit){
        u = cmul3_list(numbers, cmul3(u, (*numbers)[index]), index, limit);
    }
    return u;
}

/************************************************************/
/* Main Program                                             */
/************************************************************/

/**
 * Print complex variable
 * @param a Complex structure
 */
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

        //Use input magic to make the strings into big nums
        cpp_int real;
        cpp_int imaginary;
        df >> real >> imaginary;

        //Assemble the complex object
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

    //Read in list of numbers
    ReadListOfNumbers(std::string(argv[1]), numbers);

    // Time call to cmul4_list()
    clock_t t0, t;             // used for timing functions
    complex answer, l, r;
    int half = (numbers->size() / 2);

    t0 = clock();
    l = cmul4_list(numbers, (*numbers)[0], 0, half);
    r = cmul4_list(numbers, (*numbers)[half], half, numbers->size());
    answer = cmul4(l, r);
    t = clock() - t0;

    //std::cout << "*** CMUL4 List ***" << std::endl;
    //std::cout << "time: " << ((double) t)/CLOCKS_PER_SEC << std::endl;
    printComplex(answer);

    if(argc >= 3 && *argv[2] == '4')
        std::cout << ((double) t)/CLOCKS_PER_SEC << std::endl;


    // Time call to cmul3_list()
    t0 = clock();
    l = cmul3_list(numbers, (*numbers)[0], 0, half);
    r = cmul3_list(numbers, (*numbers)[half], half, numbers->size());
    answer = cmul3(l, r);
    t = clock() - t0;

    //std::cout << "*** CMUL3 List ***" << std::endl;
    //std::cout << "time: " << ((double) t)/CLOCKS_PER_SEC << std::endl;
    printComplex(answer);

    if(argc >= 3 && *argv[2] == '3')
        std::cout << ((double) t)/CLOCKS_PER_SEC << std::endl;

    delete numbers;
    return 0;
}
