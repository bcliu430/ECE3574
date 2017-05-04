#include <vector>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
  std::vector<double> data = {3.141592, 6.0, 1.0/3, 0.000000001};

  std::cout << "Values written to binary file." << std::endl;
  for(auto value : data){
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // open file for writing in binary mode
  std::ofstream outfile("temp.dat", std::ios_base::binary);

  // write the size of the vector in binary format
  typedef std::vector<double>::size_type SizeType;
  SizeType len = data.size();
  outfile.write(reinterpret_cast<char*>(&len), sizeof(SizeType));

  // write each entry in binary format
  for(auto value : data){
    outfile.write(reinterpret_cast<char*>(&value), sizeof(double));
  }

  outfile.close();
  
  return 0;
}
