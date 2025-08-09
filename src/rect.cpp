#include "rect.hpp"

int pixanv::Rect::clipX(int x) const
{
    if (x < left) return left;
    if (x > right)return right;
    return x;
}

int pixanv::Rect::clipY(int y) const
{
    if (y < top)return top;
    if (y > bottom)return bottom;
    return y;
}
