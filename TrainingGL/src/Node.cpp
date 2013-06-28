#include "Node.h"

namespace SolarGL
{
    Node::Node():
    _parent(NULL)
    {
        _transform.identity();
    }
}
