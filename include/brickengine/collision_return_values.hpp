struct collisionReturnValues{
    double spaceLeft;
    int objectId;
    collisionReturnValues(double spaceLeft, int objectId) : spaceLeft(spaceLeft), objectId(objectId){}
};

struct triggerReturnValues{
    bool isInTrigger;
    int objectId;
    triggerReturnValues(bool isInTrigger, int objectId) : isInTrigger(isInTrigger), objectId(objectId){}
};