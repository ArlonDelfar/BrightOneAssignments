#include <iostream>
#include <vector>

int main()
{
   int testNumber;
   std::cin >> testNumber;

   for(int t = 0; t < testNumber; ++t)
   {
      int dataNumber;                        //number of sequence elements
      std::vector<int> data;                 //sequence elements
      long long leftSum = 0, rightSum = 0;   //sum of all elements on the left and right of the current element

      std::cin >> dataNumber;
      if(dataNumber == 0)  //special case: no sequence elements
      {
         std::cout << "NO" << '\n';
         continue;
      }

      //read all sequence elements and sum them
      for(int i = 0; i < dataNumber; ++i)
      {
         int tmp;
         std::cin >> tmp;

         data.push_back(tmp);
         rightSum += tmp;
      }

      rightSum -= data[0]; //step into the first element

      //move from element to element, deducting form right sum and adding to the left sum;
      //continue until no more data or rightSum == leftSum
      for(int i = 1; i < dataNumber && rightSum != leftSum; ++i)
      {
         leftSum += data[i-1];
         rightSum -= data[i];
      }

      if(rightSum == leftSum) std::cout << "YES" << '\n';
      else std::cout << "NO" << '\n';
   }

   return 0;
}
