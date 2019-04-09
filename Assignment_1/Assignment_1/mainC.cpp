// ---------------------------------------------------------------------------
// CS 2C Assignment #1 Part C - Extra Credit (int)
#include <iostream>
#include <vector>

using namespace std;

// --------------- Sublist Prototype ---------------

template <class T>
class Sublist
{
public:
   Sublist(vector<T> *orig = NULL)
   : sum(0), originalObjects (orig) { }
   Sublist addItem( int indexOfItemToAdd );
   void showSublist() const;
   int getSum() const { return sum; }

private:
   int sum;
   vector<T> *originalObjects;
   vector<int> indices;
};

// ------------------ main ------------------

int main()
{
   int TARGET = 1000;
   vector<int> dataSet;
   vector<Sublist<int> > choices;
   vector<Sublist<int> >::iterator iter, iterBest;
   int k, j, numSets, max = 0, masterSum;
   bool foundPerfect = false;

   dataSet.push_back(20); dataSet.push_back(12); dataSet.push_back(22);
   dataSet.push_back(15); dataSet.push_back(25);
   dataSet.push_back(19); dataSet.push_back(29);
   dataSet.push_back(18);
   dataSet.push_back(11); dataSet.push_back(13); dataSet.push_back(17);

   choices.clear();
   cout << "Target time: " << TARGET << endl;

   Sublist<int> empty(&dataSet);
   choices.push_back(empty);

   for (k = 0; k < dataSet.size(); k++)
      max += dataSet[k];

   if (max <= TARGET)
   {
      cout << "TARGET (" << TARGET << ") exceeds maximum sum. \n"
      << "  sum: " << max << endl;

      for (k = 0; k < dataSet.size() - 1; k++)
         cout << "  array[" << k << "] = " << dataSet[k] << ",";

      cout << "  array[" << dataSet.size() - 1 << "] = ";
      cout << dataSet[dataSet.size() - 1] << endl << endl;
   }
   else
   {
      for (k = 0; k < dataSet.size(); k++)
      {
         numSets = choices.size();
         for (j = 0; j < numSets; j++)
         {
            if ((choices[j].getSum() + dataSet[k]) < TARGET)
               choices.push_back(choices[j].addItem(k));

            if ((choices[j].getSum() + dataSet[k]) == TARGET)
            {
               foundPerfect = true;
               choices.push_back(choices[j].addItem(k));
               break;
            }
         }
      }
      iterBest = choices.begin();
      for (iter = choices.begin() + 1; iter != choices.end(); iter++)
         if (iter->getSum() > iterBest->getSum())
            *iterBest = *iter;

      masterSum = iterBest->getSum();
      iterBest->showSublist();
   }
   return 0;
}

// --------------- Sublist Method Definitions ---------------

template <class T>
Sublist<T> Sublist<T>::addItem(int indexOfItemToAdd)
{
   Sublist newSublist = *this;
   newSublist.indices.push_back(indexOfItemToAdd);
   newSublist.sum = sum + originalObjects->at(indexOfItemToAdd);
   return newSublist;
}

template <class T>
void Sublist<T>::showSublist() const
{
   if (indices.size() == 0)
   {
      cout << "This is an empty sublist\n"
      << "{ }\n";
   }
   else
   {
      cout << "Sublist -----------------------------\n"
      << "  sum: " << sum << endl;

      for (int i = 0; i < indices.size() - 1; i++)
      {
         cout << "  array[" << indices[i] << "] = "
         << originalObjects->at(indices[i]) << ",";
      }
      cout << "  array[" << indices[indices.size() - 1] << "] = "
      << originalObjects->at(indices[indices.size() - 1]) << endl;
   }
   cout << endl;
}

/* ----------------- runs ---------------------

 Target time: 1
 This is an empty sublist
 { }

 Program ended with exit code: 0

 Target time: 67
 Sublist -----------------------------
 sum: 67
 array[0] = 20,  array[2] = 22,  array[4] = 25

 Program ended with exit code: 0

 Target time: 180
 Sublist -----------------------------
 sum: 179
 array[0] = 20,  array[1] = 12,  array[3] = 15,  array[4] = 25,  array[5] = 19,  array[6] = 29,  array[7] = 18,  array[8] = 11,  array[9] = 13,  array[10] = 17

 Program ended with exit code: 0

 Target time: 200
 Sublist -----------------------------
 sum: 190
 array[0] = 20,  array[1] = 12,  array[2] = 22,  array[3] = 15,  array[4] = 25,  array[5] = 19,  array[6] = 29,  array[7] = 18,  array[9] = 13,  array[10] = 17

 Program ended with exit code: 0

 Target time: 1000
 TARGET (1000) exceeds maximum sum.
 sum: 201
 array[0] = 20,  array[1] = 12,  array[2] = 22,  array[3] = 15,  array[4] = 25,  array[5] = 19,  array[6] = 29,  array[7] = 18,  array[8] = 11,  array[9] = 13,  array[10] = 17

 Program ended with exit code: 0

 ---------------------------------------------*/
