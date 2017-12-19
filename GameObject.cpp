#include <GameObject.h>

void
GameObject::setLocation(uint8_t x, uint8_t y) {
   m_x = x;
   m_y = y;
   m_wantToMove = false;
}

void
GameObject::setNextMovement(int8_t dx, int8_t dy) {
   m_nx = m_x + dx;
   m_ny = m_y + dy;
   m_wantToMove = true;
}