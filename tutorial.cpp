// tutorial.cpp

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include "TutorialConfig.h"

#ifdef USE_MYMATH
    #include "MathFunctions.h"
#endif

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }
    
    // get some info
    std::cout <<"Version: " << Tutorial_VERSION_MAJOR << "." << Tutorial_VERSION_MINOR << std::endl;
    std::cout << "MPI_INCLUDE PATH: " << MPI_INCLUDE << std::endl;
    std::cout << "MPI_LIBRARY PATH: " << MPI_LIBRARY << std::endl;

    // convert input to double
    const double inputValue = atof(argv[1]);

    // calculate square root
    #ifdef USE_MYMATH
      std::cout << "using custom math func!" << std::endl;
      const double outputValue = mysqrt(inputValue);
    #else
      const double outputValue = sqrt(inputValue);
    #endif

    std::cout << "The square root of " << inputValue
              << " is " << outputValue
              << std::endl;
    return 0;
}
