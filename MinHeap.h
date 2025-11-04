#ifndef MINHEAP_H
#define MINHEAP_H

#include <queue>
#include <string>
#include <vector>
using namespace std;

class MinHeap {

  struct Compare
  {
    bool operator()(const MedicineScore& lhs, const MedicineScore& rhs)
    {
      return lhs.score > rhs.score;
    }
  };

  priority_queue<MedicineScore, vector<MedicineScore>, Compare> pq;

public:

  void insertItem(const string& name, double score)
  {
    MedicineScore medicine;
    medicine.name = name;
    medicine.score = score * -1;
    pq.push(medicine);
  }

  MedicineScore extractMax()
  {
    MedicineScore max = pq.top();
    pq.pop();
    max.score = max.score * -1;
    return max;
  }

};

#endif //MINHEAP_H