// implement vtray main here
#include <iostream>
#include <QPixmap>
#include <QFile>
#include <QGuiApplication>
#include <string.h>
#include "process.hpp"

int main(int argc, char *argv[]) {


  QGuiApplication app(argc, argv);
  if (argc != 3 && argc != 5) {
    std::cout <<argc;
    std::cerr <<"Error: invalid argument number.\n";
    exit(EXIT_FAILURE);
  }
  else {
    std::string inf, outf;
    int threadNum;
    if(argc == 3){
      inf = argv[1];
      outf = argv[2];
      threadNum = 1;
      qDebug() << QString::fromStdString(inf) << QString::fromStdString(outf) << threadNum;
      process p(inf, outf, threadNum);
      return EXIT_SUCCESS;
    }
    if(argc == 5){

      if(strcmp(argv[1], "-t") == 0){
        inf = argv[3];
        outf = argv[4];
        threadNum = std::stoi(argv[2]) ;
      }
      else{
        std::cerr << "Error: should be -t <thread num> [in] [out]" << '\n';
      }
      qDebug() << QString::fromStdString(inf) << QString::fromStdString(outf) << threadNum;
      process p(inf, outf, threadNum);
      return EXIT_SUCCESS;
    }




  }

  return app.exec();
}
