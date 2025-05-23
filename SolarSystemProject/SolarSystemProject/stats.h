#pragma once
#include <iostream>
#include "SolarSpace.h"  // pentru forward-declarație a SolarSpace

namespace Solar_Stats {

    /// Structură pur de date
    struct Stats {
        int body_count{ 0 };
        float total_mass{ 0.0f };
    };

    /// Combină două Stats
    inline Stats operator+(const Stats& a, const Stats& b) {
        return Stats{ a.body_count + b.body_count,
                      a.total_mass + b.total_mass };
    }

    /// Afișează ușor
    inline std::ostream& operator<<(std::ostream& os, const Stats& s) {
        os << "[Count: " << s.body_count
            << ", Total mass: " << s.total_mass
            << "]";
        return os;
    }

    /// Colectează statistici din tot SolarSpace-ul
    inline Stats Gather(const Solar_Simulation::SolarSpace& space) {
        Stats st;
        for (auto body : space.GetEntities()) {
            ++st.body_count;
            st.total_mass += body->getMass();
        }
        return st;
    }

} // namespace Solar_Stats
