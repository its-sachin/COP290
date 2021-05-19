enum LR : unsigned char{
    LEFT, 
    RIGHT
};

enum UD: unsigned char{
    FRONT, 
    DOWN, 
    UP
};

enum PlayMode: unsigned char{
    Single, 
    Doffline, 
    Donline
};

enum Move: unsigned char{

    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    STATIC

};

enum Stone: unsigned char{

    MIND,
    SPACE,
    TIME,
    POWER,
    REALITY,
    SOUL,
    NONE
};

enum EnemyState: unsigned char{

    FRIGHTENED,
    SCATTER,
    CHASE,
    DIE
};



