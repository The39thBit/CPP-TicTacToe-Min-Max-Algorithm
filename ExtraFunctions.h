#pragma once
#include <vector>
#include <cstdlib>
#include "TicTacToeVector.h"
#include <string>
#include <ctype.h>
#include <iostream>
#include <fstream>

class my_ostream
{
public:
    my_ostream() : my_fstream("Output.txt") {}; // check if opening file succeeded!!
    // for regular output of variables and stuff
    template<typename T> my_ostream& operator<<(const T& something)
    {
        
        my_fstream << something;
        return *this;
    }
    // for manipulators like std::endl
    typedef std::ostream& (*stream_function)(std::ostream&);
    my_ostream& operator<<(stream_function func)
    {
        //func(std::cout);
        func(my_fstream);
        return *this;
    }
private:
    std::ofstream my_fstream;
};
class my_rstream
{
public:
    my_rstream() : my_fstream("GameResult.txt") {}; // check if opening file succeeded!!
    // for regular output of variables and stuff
    template<typename T> my_rstream& operator<<(const T& something)
    {

        my_fstream << something;
        return *this;
    }
    // for manipulators like std::endl
    typedef std::ostream& (*stream_function)(std::ostream&);
    my_rstream& operator<<(stream_function func)
    {
        //func(std::cout);
        func(my_fstream);
        return *this;
    }
private:
    std::ofstream my_fstream;
};
int VectorToInt(std::vector<int> v)
{
    reverse(v.begin(), v.end());
    int decimal = 1;
    int total = 0;
    for (auto& it : v)
    {
        total += it * decimal;
        decimal *= 10;
    }
    return total;
}
std::string VectorToString(std::vector<int> v)
{
    std::string str = "";
    char temp;
    for(int it = 0;it<v.size();it++)
    { 
        char temp = v[it]+48;
        str += temp;

     
    }
    return str;
}
int VectorRandomChoose(std::vector<int> v) {
    srand((unsigned)time(NULL));
    int random = rand();
    return random % v.size();

}

int GetLastDigit(int ChildPath) {

    std::string CheckPath = std::to_string(ChildPath);
    char Val = CheckPath[CheckPath.length()-1];
    return int(Val) - 48;
}
    
