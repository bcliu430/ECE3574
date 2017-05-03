////////////////////////////////////////////////////////////////////////////////
// Filename:      main.cpp
// Name:          Beichen Liu 刘北辰
// Description:   This is the main file for vtscript
// Last Modified: ver.02-01-2017 File Created
//                ver.03-01-2017 file update
// TODO:
//

#include <iostream>
#include <fstream>
#include <string>

#include "interpreter.hpp"
#include "expression.hpp"
#include "tokenize.hpp"
#include "environment.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    Interpreter i;
    if (argc > 3 ){
        exit(EXIT_FAILURE);
    }
    else if( argc == 3){
        if (argv[1] != string("-e") ) {
            cerr <<  "Error: Invalid arguments\n";
            exit(EXIT_FAILURE);
        }
        else {
            string expre = argv[2];
            istringstream iss(expre);
            if(i.parse(iss)){
              Expression answer;
              try {
                  answer = i.eval();
                  cout << "(" ;
                  answer.DisplayResult();
                  cout << ")\n" ;
                  }
              catch (const InterpreterSemanticError &err) {
                  std::cerr << "Error: " << err.what() << '\n';
                  return EXIT_FAILURE;
                }
            }
            else{
                cerr << "Error: Failed to parse " << argv[2] << '\n';
                exit(EXIT_FAILURE);
            }


        }
    }
    else if (argc == 2){
          ifstream inf(argv[1]);
          if(i.parse(inf)){
            Expression answer;
            try {
                answer = i.eval();
                cout << "(" ;
                answer.DisplayResult();
                cout << ")\n" ;
                }
            catch (const InterpreterSemanticError &err) {
                std::cerr << "Error: " << err.what() << '\n';
                return EXIT_FAILURE;
              }
          }
          else{
              cerr << "Error: Failed to parse " << argv[1]<< '\n';
              exit(EXIT_FAILURE);
          }



    }
    else if (argc == 1){
        Interpreter i;
        while(true){
            string in;
            cout << "vtscript> ";
            getline(cin,in,'\n');
            if(in.size()!= 0) {
                istringstream iss(in);
                Interpreter i;
                bool parse_success;
                parse_success = i.parse(iss);

                if(parse_success){
                    Expression answer;
                    try {
                        answer = i.eval();
                        cout << "(" ;
                        answer.DisplayResult();
                        cout << ")\n" ;
                        }
                    catch (const InterpreterSemanticError &err) {
                        std::cerr << "Error: " << err.what() << '\n';
                      }
                }
                else{
                      cerr << "Error: Failed to parse " << in << '\n';
                    exit(EXIT_FAILURE);
                    }

            }

        }
    }
    else
        exit(EXIT_FAILURE);
    return 0;
  }
