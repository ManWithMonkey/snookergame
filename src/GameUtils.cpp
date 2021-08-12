#include "GameUtils.hpp"

void Line::UpdateNormal(){
    nu = NormalUnit(b - a);
}
