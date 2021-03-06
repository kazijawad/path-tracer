#ifndef aabb_h
#define aabb_h

#include <cmath>
#include <algorithm>

#include "vec3.h"

class aabb {
public:
    aabb() {}
    aabb(const vec3& a, const vec3& b) : minimum(a), maximum(b) {}

    vec3 min() const {
        return minimum;
    }

    vec3 max() const {
        return maximum;
    }

    bool hit(const ray& r, double t_min, double t_max) const {
        for (int a = 0; a < 3; a++) {
            auto invD = 1.0f / r.direction()[a];
            auto t0 = (minimum[a] - r.origin()[a]) * invD;
            auto t1 = (maximum[a] - r.origin()[a]) * invD;
            if (invD < 0.0f) {
                std::swap(t0, t1);
            }
            t_min = t0 > t_min ? t0 : t_min;
            t_max = t1 < t_max ? t1 : t_max;
            if (t_max <= t_min) {
                return false;
            }
        }
        return true;
    }

    static aabb surrounding_box(aabb box0, aabb box1) {
        auto small = vec3(
            fmin(box0.min().x(), box1.min().x()),
            fmin(box0.min().y(), box1.min().y()),
            fmin(box0.min().z(), box1.min().z())
        );
        auto big = vec3(
            fmax(box0.max().x(), box1.max().x()),
            fmax(box0.max().y(), box1.max().y()),
            fmax(box0.max().z(), box1.max().z())
        );
        return aabb(small, big);
    }

private:
    vec3 minimum;
    vec3 maximum;
};

#endif
