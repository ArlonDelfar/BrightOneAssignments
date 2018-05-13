#include <fstream>
#include <iostream>
#include <string>
#include <cctype>       //isxdigit
#include <vector>
#include <algorithm>

std::vector<unsigned char> readDataAsHex(char const* inputFileName)
{
   std::ifstream inputFile(inputFileName);
   std::vector<unsigned char> outputVector;

   if(inputFile)
   {
      std::string hexBufor;
      char letterBufor;
      while(inputFile >> letterBufor)
      {
         //filter non-hex-digits
         if(isxdigit(letterBufor)) hexBufor += letterBufor;

         //convert 2s of hexdigits into 8bit numbers
         if(hexBufor.size() == 2)
         {
            outputVector.push_back(stoi(hexBufor, nullptr, 16));
            hexBufor.clear();
         }
      }
      //check for leftover single hex-digit data and convert if needed
      if(hexBufor.size() == 1) outputVector.push_back(stoi(hexBufor, nullptr, 16));
   }
   else std::cout << "File \"" << inputFileName << "\" does not exist" << '\n';

   return outputVector;
}

void saveData(const std::vector<unsigned char> &evens, const std::vector<unsigned char> &odds,
               char const* outputFileName)
{
   if(evens.size() == 0 && odds.size() == 0) return;
   std::ofstream outputFile(std::string(outputFileName) + ".out");

   outputFile << "evens: " << '\n';
   for(int i = 0; i < evens.size(); ++i)
      outputFile << (int)evens[i] << '\n';

   outputFile << '\n' << "odds: " << '\n';
   for(int i = 0; i < odds.size(); ++i)
      outputFile << (int)odds[i] << '\n';
}

#if defined(__GNUC__)
int getBitCount(unsigned char c)
{
   return __builtin_popcount(c);
}

#else
int getBitCount(unsigned char c)
{
   int count = 0;
   //Brian Kerningham's Algorithm
   while(c)
   {
      c = c & (c-1);
      count++;
   }
   return count;
}
#endif

int main(int argc, char const *argv[]) {
   if(argc < 2) return 1;
   for(int t = 1; t < argc; ++t)
   {
      std::vector<unsigned char> outputVector = readDataAsHex(argv[1]);
      std::vector<unsigned char> evens;
      std::vector<unsigned char> odds;

      for(int i = 0; i < outputVector.size(); ++i)
      {
         if(getBitCount(outputVector[i]) % 2 == 0)
            evens.push_back(outputVector[i]);
         else
            odds.push_back(outputVector[i]);
      }

      std::sort(evens.begin(), evens.end());
      std::sort(odds.begin(), odds.end(), std::greater<unsigned char>());

      saveData(evens, odds, argv[t]);
   }
   return 0;
}
