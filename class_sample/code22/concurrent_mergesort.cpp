#include <vector>
#include <algorithm>
#include <random>
#include <thread>
#include <future>
#include <iostream>

typedef std::vector<double> ArrayType;

// list size threshold for which we switch between
// serial and concurrent. Lists below this size
// are sorted using sequential mergesort
const int SWITCH_SIZE = 1000; 

void merge(ArrayType& theArray, int first, int mid, int last)
{
  ArrayType tempArray(theArray.size());
  
  int first1 = first;
  int last1  = mid;  
  int first2 = mid + 1;
  int last2  = last;
  
  int index = first1;    
  for (; (first1 <= last1) && (first2 <= last2); ++index){  
    if (theArray[first1] <= theArray[first2]){
      tempArray[index] = theArray[first1];
      ++first1;
    }
    else{
      tempArray[index] = theArray[first2];
      ++first2;
    }
  }
  
  for (; first1 <= last1; ++first1, ++index)
    tempArray[index] = theArray[first1];
  
  for (; first2 <= last2; ++first2, ++index)
    tempArray[index] = theArray[first2];
  
  for (index = first; index <= last; ++index)
    theArray[index] = tempArray[index];
} 

// crazy bug story
// it took me an hour to figure out I could not name this mergesort
// because mergesort is previously defined in cstdlib!
void msort(ArrayType& theArray, int first, int last)
{ 
  if (first < last){
    
    int mid = (first + last) >> 1;

    if((last - first) > SWITCH_SIZE){
      // block scope forces furture destructor and thus wait on async calls
      auto fut0 = std::async(&msort, std::ref(theArray), first, mid);
      auto fut1 = std::async(&msort, std::ref(theArray), mid+1, last);
    }
    else{
      msort(theArray, first, mid);
      msort(theArray, mid+1, last);
    }
    
    merge(theArray, first, mid, last);
  }

}

// a normal distributed random number generator
class fill_normal
{
public:

  fill_normal()
  {
    std::random_device rd;
    gen.seed(rd());
  }
  
  void operator()(double & x)
  {
    x = p(gen);
  }

private:
  std::mt19937 gen;
  std::normal_distribution<double> p; 
};


int main()
{
  std::cout << "Sorting Using Concurrent Mergesort\n";
  std::cout << "------------------------------" << std::endl;
  std::cout << "Size\tElapsed Time (s)" << std::endl;
  for(long N = 10; N < 500000; N = 2*N){
    ArrayType data(N);
    fill_normal d;
    for_each(data.begin(), data.end(), d);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;

    // time serial
    start = std::chrono::system_clock::now();
    msort(data, 0, data.size()-1);
    end = std::chrono::system_clock::now();
    
    elapsed_seconds = end-start;
    std::cout << N <<  "\t" << elapsed_seconds.count() << std::endl;
  }
  
  return 0;
}
