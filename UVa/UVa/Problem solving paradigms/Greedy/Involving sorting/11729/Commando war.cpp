//
// Created by gautham on 13/9/18.
//

// WA
#include <vector>
#include <algorithm>
#include <iostream>

struct Task {
  Task() : brief_time(0), job_time(0) {}
  Task(int brief_time, int job_time) : brief_time(brief_time), job_time(job_time) {}

  int brief_time;
  int job_time;
};

class Ordering {
 public:
  explicit Ordering(std::vector<Task> task_list);
  long TotalTime() const;

 private:
  std::vector<Task> task_list_;
};

Ordering::Ordering(std::vector<Task> task_list) : task_list_(std::move(task_list)) {
  std::sort(task_list_.begin(), task_list_.end(), [](const Task &m, const Task &n) -> bool {
    if (m.job_time == n.job_time) {
      return m.brief_time < n.brief_time;
    }
    return m.job_time > n.job_time;
  });
}

long Ordering::TotalTime() const {
  long brief_timeline = 0, job_timeline = 0;

  for (const auto &task : task_list_) {
    brief_timeline += task.brief_time;
    job_timeline = brief_timeline + task.job_time;
  }
  return job_timeline;
}

int main() {
  std::size_t n, t = 0;
  std::vector<Task> task_list{
      {5, 2},
      {6, 4},
      {2, 3}
  };

  while (std::cin >> n, n) {
    task_list.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
      std::cin >> task_list[i].brief_time >> task_list[i].job_time;
    }

    std::cout << "Case " << ++t << ": " << Ordering(task_list).TotalTime() << std::endl;
  }
  return 0;
}