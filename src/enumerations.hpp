#ifndef DXNA_ENUMERATIONS_HPP
#define DXNA_ENUMERATIONS_HPP

namespace dxna {
    enum class DisplayOrientation {
        Default = 0,
        LandscapeLeft = 1,
        LandscapeRight = 2,
        Portrait = 4,
    };

    enum class PlaneIntersectionType {
        Front,
        Back,
        Intersecting,
    };

    enum class ContainmentType {
        Disjoint,
        Contains,
        Intersects,
    };

    enum class CurveContinuity {
        Smooth,
        Step,
    };

    enum class CurveTangent {
        Flat,
        Linear,
        Smooth,
    };

    enum class CurveLoopType {
        Constant,
        Cycle,
        CycleOffset,
        Oscillate,
        Linear,
    };
}

#endif