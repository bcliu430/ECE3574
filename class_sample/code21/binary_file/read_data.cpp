#include <vector>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
  std::vector<double> data;

  // open file for reading in binary mode
  std::ifstream infile("temp.dat", std::ios_base::binary);

  // read the size of the vector in binary format
  typedef std::vector<double>::size_type SizeType;
  SizeType len;
  infile.read(reinterpret_cast<char*>(&len), sizeof(SizeType));
  data.resize(len);
  
  // read each entry in binary format
  for(SizeType i = 0; i < len; ++i){
    double value;
    infile.read(reinterpret_cast<char*>(&value), sizeof(double));
    data[i] = value;
  }

  infile.close();

  std::cout << data.size() << " values read from binary file." << std::endl;
  for(auto value : data){
    std::cout << value << " ";
  }
  std::cout << std::endl;
  
  return 0;
}
