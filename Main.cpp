// Main.cpp : Holds the main() function and needs all others through include
//

#include <iostream>
#include <stdlib.h> 
#include <string>
#include <vector>
#include "testingWindow.hpp"

int main()
{
    bool valid = false;
    while (!valid) {
        std::cout << "Please enter an option from those provided below:" << std::endl;
        std::cout << "\t[0] Open test window" << std::endl;
        std::cout << "\t[1] Open Audio Program (NOT IMPLEMENTED)" << std::endl;
        std::cout << "\t[2] Open Character Sheet Program (NOT IMPLEMENTED)" << std::endl;
        std::cout << "\t[-1] Cancel/Exit program" << std::endl;

        std::string input = "";
        std::cin >> input;
        int choice = -1;

        try {
            choice = std::stoi(input);
        }
        catch (std::exception e) {
            system("cls");
            std::cout << "Invalid input (NaN). Please try again." << std::endl << std::endl;
            continue;
        }

        switch (choice)
        {
        case -1:
            exit(0);
            break;
        case 0:
            valid = true;
            runTestWindow();
            break;
        case 1:
            exit(1);
            break;
        case 2:
            exit(2);
            break;
        default:
            system("cls");
            std::cout << "Invalid input (Not a choice). Please try again." << std::endl << std::endl;
        }


    }

    return 0;
}