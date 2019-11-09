#ifndef FILE_KINEMATIC_HPP
#define FILE_KINEMATIC_HPP

// When using this enum in a system, use kinematic != IS_KINEMATIC or kinematic == IS_KINEMATIC
// to automaticly include or exclude the SHOULD_NOT_BE_KINEMATIC value
enum class Kinematic {
    IS_KINEMATIC,
    // This value should act the same as IS_KINEMATIC, however when a child is released
    // this value will get changed back to the original IS_NOT_KINAMTIC value
    SHOULD_NOT_BE_KINEMATIC,
    IS_NOT_KINEMATIC
};

#endif // FILE_KINEMATIC_HPP