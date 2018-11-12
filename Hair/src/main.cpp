#include <iostream>
#include "Hair.h"

int main()
{
    ngl::Vec3 headPosition(1, 2, 0);
    Hair h(headPosition, 2.0f, 100);
    h.render();
}
