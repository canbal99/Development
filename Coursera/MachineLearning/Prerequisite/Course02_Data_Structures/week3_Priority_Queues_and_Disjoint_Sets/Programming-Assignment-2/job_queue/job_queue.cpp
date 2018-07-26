#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::tuple;
using std::get;
using std::priority_queue;
using std::make_tuple;

struct Thread {
    int index;
    long long available = 0;
    
    Thread(int i):index(i) {};
};

struct CompareAvailableThread
{
  bool operator()(const Thread& lhs, const Thread& rhs) const
  {
      if (lhs.available != rhs.available)
        return lhs.available > rhs.available;
      return lhs.index > rhs.index;
  }
};

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;
  
public:
  JobQueue() {}
  
  JobQueue(int num_workers, vector<int>& jobs) {
      num_workers_ = num_workers;
      for (int job : jobs) {
          jobs_.push_back(job);
      }
  }
  
private:
  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
    
    cout << "read completed\n";
  }

public:
  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    //vector<long long> next_free_time(num_workers_, 0);
    
    priority_queue<Thread, std::vector< Thread >, CompareAvailableThread> thread_available;
    for (int i=0; i<num_workers_;i++) {
        thread_available.push(Thread(i));
    }
    
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      
      /*for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }*/
      Thread available = thread_available.top();
      
      assigned_workers_[i] = available.index;
      start_times_[i] = available.available;
      
      thread_available.pop();
      available.available += duration;
      thread_available.push(available);
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

bool compare(int numOfWorkers, vector<int> jobs) {
    clock_t begin_time, end_time;
    JobQueue job_queue(numOfWorkers, jobs);
    begin_time = clock();
    job_queue.AssignJobs();
    end_time = clock();
    std::cout << "JobQueue: " << numOfWorkers << "-" << jobs.size() << " in " << (end_time-begin_time)/1000 << "ms\n";
    return (end_time-begin_time)/1000<100;
}

#define RANDOM()   (rand()%10000)
void test_solution() {
    const int TEST_COUNT = 100;
    std::cout << "Test started !!!\n";
    for (int i=0;i<TEST_COUNT;i++) {
        int size = 100000;//1+(rand()%100000);
        std::cout << "Test for " << i << ":" << size << "\n";
        vector<int> x(size);
        for (int j=0;j<size;j++) {
            x[j] = RANDOM();
        }
        if (!compare(10000,x)) {
            std::cout << "error!!!\n";
            return;
        }
    }
    std::cout << "Test succeeded !!!\n";
}

int main() {
    //test_solution();
    //return 0;
    
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
