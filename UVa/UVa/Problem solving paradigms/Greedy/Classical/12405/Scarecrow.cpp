//
// Created by gautham on 2/8/18.
//

#include <iostream>
#include <string>
#include <queue>
#include <cassert>

struct ScanInfo {
  ScanInfo() : coverage(0), i_scarecrow(0), miss(false) {}
  ScanInfo(int coverage) : coverage(coverage), i_scarecrow(0), miss(false) {}

  bool operator>(const ScanInfo &other) const {
    return coverage == other.coverage ? i_scarecrow > other.i_scarecrow : coverage < other.coverage;
  }

  int coverage;
  std::size_t i_scarecrow;
  bool miss;
};

using Scans = std::priority_queue<ScanInfo, std::vector<ScanInfo>, std::greater<ScanInfo>>;

class Field {
 public:
  explicit Field(std::string field) : field_(std::move(field)) {}

  ScanInfo Scan(std::size_t i) const;
  void Mark(std::size_t i);
  std::size_t Length() const { return field_.length(); }

 private:
  std::string field_;
};

ScanInfo Field::Scan(std::size_t i) const {
  assert(!field_.empty());

  if (field_.length() == 1) {
    return {field_[0] == '.' ? 1 : 0};
  }

  ScanInfo info;
  if (i > 0) {
    info.coverage = (field_[i - 1] == '.' ? 1 : 0) + info.coverage;
  }

  if (i < field_.length()) {
    info.coverage = (field_[i] == '.' ? 1 : 0) + info.coverage;
  }

  if (i + 1 < field_.length()) {
    info.coverage = (field_[i + 1] == '.' ? 1 : 0) + info.coverage;
  }

  if (i > 1) {
    info.miss = field_[i - 2] == '.';
  }

  info.i_scarecrow = i;
  return info;
}

void Field::Mark(std::size_t i) {
  assert(!field_.empty());
  assert(i < field_.length());

  if (field_.length() == 1) {
    field_[0] = '#';
    return;
  }

  field_[i] = '#';
  if (i > 0) {
    field_[i - 1] = '#';
  }

  if (i + 1 < field_.length()) {
    field_[i + 1] = '#';
  }
}

class ScarecrowAllocator {
 public:
  explicit ScarecrowAllocator(const std::string &field) : field_(Field(field)) {}
  int Minimal();

 private:
  Field field_;
};

int ScarecrowAllocator::Minimal() {
  int num_scarecrows = 0;
  Scans scans;

  for (std::size_t i = 0; i < field_.Length(); ++num_scarecrows) {
    for (; i < field_.Length(); ++i) {
      auto info = field_.Scan(i);
      if (info.coverage != 0) {
        scans.emplace(info);
      }

      if (info.miss) {
        break;
      }
    }

    if (scans.empty()) {
      break;
    }

    auto info = scans.top();
    field_.Mark(info.i_scarecrow);
    i = info.i_scarecrow + 2;
    Scans().swap(scans);
  }

  return num_scarecrows;
}

int main() {
  std::string field;
  int t, field_length;
  std::cin >> t;
  for (int i = 1; i <= t; ++i) {
    std::cin >> field_length >> field;
    std::cout << "Case " << i << ": " << ScarecrowAllocator(field).Minimal() << std::endl;
  }

  return 0;
}