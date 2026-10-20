#ifndef UNO_TYPES_HPP
#define UNO_TYPES_HPP

enum class Color {
    Red,
    Yellow,
    Green,
    Blue,
    None
};
enum class CardType {
    Number,
    Skip,
    Reverse,
    DrawTwo,
    Wild,
    WildDrawFour
};
enum class Direction {
    Clockwise,
    CounterClockwise
};

#endif
