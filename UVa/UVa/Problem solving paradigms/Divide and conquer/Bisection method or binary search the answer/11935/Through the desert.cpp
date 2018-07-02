//
// Created by gauth on 01-07-2018.
//

#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <queue>
#include <cassert>

enum EventType {
    kFuelConsumption, kLeak, kGasStation, kMechanic, kGoal
};

struct Event {
    Event() : distance(0), value(0), type(EventType::kFuelConsumption) {}

    int distance;
    int value;
    EventType type;
};

EventType GetEventType(const std::string &event_name) {
    if (event_name[0] == 'F') {
        return EventType::kFuelConsumption;
    }

    if (event_name[0] == 'L') {
        return EventType::kLeak;
    }

    if (event_name[0] == 'M') {
        return EventType::kMechanic;
    }

    if (event_name[1] == 'a') {
        return EventType::kGasStation;
    }

    assert(event_name[1] == 'o');

    return EventType::kGoal;
}

Event ParseEvent(const std::string &event_str) {
    Event event;
    std::string event_name;
    std::istringstream tokenizer(event_str);

    tokenizer >> event.distance;

    tokenizer >> event_name;
    event.type = GetEventType(event_name);
    if (event.type == EventType::kFuelConsumption) {
        tokenizer >> event_name;
        tokenizer >> event.value;
    }

    return event;
}

float Simulate(const std::list<Event> &events) {
    int leaks = 0, previous_distance = 0;
    float fuel_needed = 0.0f, consumption_rate;
    std::priority_queue<float> fuel_requirements;

    auto it = events.begin();
    auto event = *it;
    assert(event.type == EventType::kFuelConsumption);

    previous_distance = event.distance;
    consumption_rate = event.value / 100.0f;

    for (++it; it != events.end(); ++it) {
        event = *it;

        auto distance_covered = event.distance - previous_distance;
        fuel_needed += distance_covered * (consumption_rate + leaks);

        switch (event.type) {
            case kFuelConsumption:
                consumption_rate = event.value / 100.0f;
                break;

            case kLeak:
                ++leaks;
                break;

            case kGasStation:
                fuel_requirements.emplace(fuel_needed);
                fuel_needed = 0.0f;
                break;

            case kMechanic:
                leaks = 0;
                break;

            case kGoal:
                break;
        }

        previous_distance = event.distance;
    }

    fuel_requirements.emplace(fuel_needed);
    return fuel_requirements.top();
}

int main() {
    std::string line;
    std::list<Event> events;

    while (std::getline(std::cin, line), !std::cin.eof()) {
        auto event = ParseEvent(line);
        events.emplace_back(event);

        if (event.type == EventType::kGoal) {
            printf("%.3f\n", Simulate(events));
            events.clear();
        }
    }

    return 0;
}