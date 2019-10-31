#include <optional>

struct CollisionReturnValues{
    CollisionReturnValues(double spaceLeft, int objectId) : spaceLeft(spaceLeft), objectId(objectId) {}
    double spaceLeft;
    int objectId;
};

struct TriggerReturnValues{
    TriggerReturnValues(bool isInTrigger, int objectId) : isInTrigger(isInTrigger), objectId(objectId) {}
    bool isInTrigger;
    std::optional<int> objectId;
};