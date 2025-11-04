//https://www.youtube.com/watch?v=6jwj2WIRvTE


#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;


// class Medicine {
// public:
//     string name;
//     string category;
//     string dosage;
//     string strength;
//     string indication;
//     string classification;
//
//     Medicine() {
//
//     }
// };


struct MedicineScore {
   string name;
   double score;
};

//heap contains a vector and a count of amount of items it has


//https://www.youtube.com/watch?v=6jwj2WIRvTE
class MaxHeap {
private:
   int _size{}; // value-initialized to 0, count of amount of items vector has
   // vector<int> vect = {-1}; // start with rand # we wont touch
   vector<MedicineScore> vect = {MedicineScore{"", -1}};


   int parent(int index) { //given index, give us parent node
       return index>>1; // = index / 2 (shifts 1 bit right)
   }


   int left_child(int index) {
       return index<<1; // index * 2
   }


   int right_child(int index) {
       return (index<<1) + 1;
   }


public:
   bool isEmpty() const {
       return _size == 0;
   }


   MedicineScore getMax() const {
       return vect[1];
   }


   void insertItem(const string& name, double score);
   void shiftUp(int index); // in order to insert, we must shift up, takes index of item we are inserting
   MedicineScore extractMax();
//in order to extract max, we swap it with the smallest element, then we recursively push the smallest element down until it arrives at its proper position
   void shiftDown(int index);
//in order to extract, we must shift down
};


void MaxHeap::shiftUp(int index) {
   if (index > _size) {//trying to shift up index that doesn't exist
       return;
   }
   if (index == 1) {//return from recursion when we get to top element
       return;
   }
   if (vect[index].score > vect[parent(index)].score) {
       swap(vect[parent(index)], vect[index]);
   }
   shiftUp(parent(index)); //perform same operation on parent -> is parent's parent greater or smaller than parent?
}


void MaxHeap::insertItem(const string& name, double score) {
   if (_size + 1 >= vect.size()) {
       vect.push_back(MedicineScore{"", 0.0}); //push back place holder
   }
   MedicineScore newMed;
   newMed.name = name;
   newMed.score = score;
   vect[++_size] = newMed; //adding item where placeholder is
   shiftUp(_size); //shifts element up to proper position
}


void MaxHeap::shiftDown(int index) {
   if (index > _size) {
       return;
   }
   int swapId = index; //we're comparing parent to two children
   //keeps track of which node has largest value
   if (left_child(index) <= _size && vect[index].score < vect[left_child(index)].score) {
       swapId = left_child(index);
   }


   if (right_child(index) <= _size && vect[swapId].score < vect[right_child(index)].score) {
       swapId = right_child(index); //swap right child with parent instead
   }


   //stop recursion when swapId = index
   if (swapId != index) {
       swap(vect[index], vect[swapId]); //swap parent with largest child
       shiftDown(swapId); //recurse to child
   }
}


MedicineScore MaxHeap::extractMax() {
   MedicineScore maxNum = vect[1];
   swap(vect[1], vect[_size--]);
   shiftDown(1);
   return maxNum;
}


//https://www.geeksforgeeks.org/cpp/pair-in-cpp-stl/
//https://www.geeksforgeeks.org/cpp/std-find-in-cpp/
int computeScore(const pair<const string, vector<string>>& medicine_entry, const vector<string>& userSelections) {
   const vector<string>& characteristics = medicine_entry.second;
   int score = 0;


   for (const string& choice : userSelections) {
       // Check if the medicine contains this characteristic
       if (find(characteristics.begin(), characteristics.end(), choice) != characteristics.end()) {
           score += 1; // Add 1 point per match (you can tweak this)
       }
   }


   return score;
}


// int main() {
//    ifstream file("C:/Project2/medicine_dataset.csv"); // adjust filename as needed
//    if (!file.is_open()) {
//        cerr << "Failed to open file.\n";
//        return 1;
//    }
//
//
//    unordered_map<string, vector<string>> medicineTable; //hashmap
//
//
//    // string line = "Dextromet,Antiseptic,Tablet,287 mg,AbbVie Inc.,Diabetes,Prescription";
//    string line;
//    while (getline(file, line)) { //for each line in the dataset
//        // Read line by line
//        stringstream streamofstring(line);  // Create a stringstream from the line from dataset
//        string segment;
//        vector<string> medicine_data; // To store the split values of the current row of data
//
//
//        while (getline(streamofstring, segment, ',')) { //split line into segments separated by the commas
//            medicine_data.push_back(segment);
//           // "Dextromet Antiseptic Tablet 287 mg AbbVie Inc. Diabetes Prescription"
//        }
//
//
//        vector<string> medicineCharacteristics; //contains characteristics of each medicine, minus the name
//        for(int i = 1; i < medicine_data.size(); i++){
//            medicineCharacteristics.push_back(medicine_data[i]);
//        }
//
//
//        //inserting into hashmap the name of each Medicine and a vector containing its characteristics
//        medicineTable.insert({medicine_data[0],medicineCharacteristics});
//
//
//    }
//
//
//
//
//
//
//    vector<string> userSelections = {"Syrup", "Depression", "Prescription", "Antifungal"};
//    MaxHeap heap;
//    for (auto& entry : medicineTable) {
//        double score = computeScore(entry, userSelections);
//        heap.insertItem(entry.first, score);
//    }
//    MedicineScore best = heap.extractMax();
//    cout << "Best match: " << best.name << " (score = " << best.score << ")" << endl;
//    file.close();
//    return 0;
// }
