#include <iostream>
#include <string>

const double PI = 3.14159;
using Meters = double;

int area(int redius);   // Function prototype (declaration)


int main(){
    Meters r = 5.0;
    std::cout << "area = " << area(static_cast<int>(r)) << "\n";
    return 0;
}


int area(int redius){
   return static_cast<int>(PI*redius*redius);
}
