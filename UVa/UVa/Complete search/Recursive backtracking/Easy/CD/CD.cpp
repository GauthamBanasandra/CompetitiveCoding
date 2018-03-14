//
// Created by gauth on 14-03-2018.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using ull = unsigned long long;

struct TracksInfo {
  TracksInfo() : selected_tracks(0), n_selected_tracks(0), total_duration(0) {}

  int selected_tracks;
  int n_selected_tracks;
  ull total_duration;

  bool operator>(const TracksInfo &other) {
    if (total_duration > other.total_duration) {
      return true;
    } else if (total_duration == other.total_duration && n_selected_tracks > other.n_selected_tracks) {
      return true;
    }

    return false;
  }
};

TracksInfo ChooseTracks(int max_duration, int selected_tracks, const std::vector<int> &durations) {
  TracksInfo info;
  for (auto i = 0; selected_tracks; selected_tracks >>= 1, ++i) {
    if (selected_tracks & 1) {
      if (info.total_duration + durations[i] > max_duration) {
        return info;
      }

      info.total_duration += durations[i];
      info.selected_tracks |= (1 << i);
      ++info.n_selected_tracks;
    }
  }

  return info;
}

std::string GetBestTracks(int max_duration, int n_tracks, const std::vector<int> &durations) {
  auto initialized = false;
  TracksInfo best_tracks_info;
  std::string best_tracks;

  for (int i = 0; i < (1 << n_tracks); ++i) {
    if (!initialized) {
      best_tracks_info = ChooseTracks(max_duration, i, durations);
      initialized = true;
      continue;
    }

    auto tracks_info = ChooseTracks(max_duration, i, durations);
    if (tracks_info > best_tracks_info) {
      best_tracks_info = tracks_info;
    }
  }

  for (auto i = 0; best_tracks_info.selected_tracks; best_tracks_info.selected_tracks >>= 1, ++i) {
    if (best_tracks_info.selected_tracks & 1) {
      best_tracks += std::to_string(durations[i]) + " ";
    }
  }

  best_tracks += "sum:" + std::to_string(best_tracks_info.total_duration);
  return best_tracks;
}

int main() {
  int n, n_tracks, duration;
  std::string line;
  std::vector<int> durations;

  while (std::getline(std::cin, line), !std::cin.eof()) {
    durations.clear();

    std::istringstream tokenizer(line);
    tokenizer >> n >> n_tracks;
    for (int i = 0; i < n_tracks; ++i) {
      tokenizer >> duration;
      durations.push_back(duration);
    }

    std::cout << GetBestTracks(n, n_tracks, durations) << std::endl;
  }

  return 0;
}