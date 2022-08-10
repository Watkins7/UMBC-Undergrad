//
// Created by Thadd-PC on 4/7/2020.
//

#include "Creature.h"

Creature::Creature() {}
Creature::Creature(string name, int health, int attack) {
    m_name = name;
    m_health = health;
    m_attack = attack;
}
