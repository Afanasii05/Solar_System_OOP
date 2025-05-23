#pragma once

#include <ostream>
#include <SFML/System/Vector2.hpp>

namespace Math {

    // Structura pentru vector 2D
    template<typename T>
    struct Vec2 {
        T x;
        T y;

        // Constructori
        constexpr Vec2() noexcept = default;
        constexpr Vec2(float _x, float _y) noexcept : x(_x), y(_y) {}

        // Operator+ (adunare)
        Vec2 operator+(const Vec2& rhs) const noexcept {
            return Vec2{ x + rhs.x, y + rhs.y };
        }

        // Operator- (scadere)
        Vec2 operator-(const Vec2& rhs) const noexcept {
            return Vec2{ x - rhs.x, y - rhs.y };
        }

        // Operator*= (scalare în loc)
        Vec2& operator*=(float scalar) noexcept {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        // Operator* (scalare, returneaza valoric)
        Vec2 operator*(float scalar) const noexcept {
            Vec2 tmp = *this;
            tmp *= scalar;
            return tmp;
        }
    };

    // Supraincarcare operator<< pentru debug
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, const typename Vec2<T> &v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }

    // Conversie SFML <-> Vec2
    template<typename T>
    inline Vec2<T> FromSF(const sf::Vector2f& v) {
        return Vec2{ v.x, v.y };
    }
    template<typename T>
    inline sf::Vector2f ToSF(const typename Vec2<T> &v) {
        return sf::Vector2f{ v.x, v.y };
    }

} // namespace Math
