#ifndef HORROR_CITIZEN_H
#define HORROR_CITIZEN_H

#include <cassert>
#include <iostream>

const int ADULT_MIN_AGE = 18;
const int ADULT_MAX_AGE = 100;
const int TEEN_MIN_AGE = 11;
const int TEEN_MAX_AGE = 17;

template <typename T, int lower, int upper, bool isAttacking>
class Citizen {
private:
    T health_;
    T age_;
    T attackPower_;
public:
    /**
     * Constructor for not attacking citizen (adult, teenager)
     */
    template <typename Q = T, typename = typename std::enable_if_t<!isAttacking, Q> >
    Citizen(T health, T age) : health_(health), age_(age) { assert(age >= lower && age <= upper); }

    /**
     * Constructor for sheriff.
     */
    template <typename Q = T, typename = typename std::enable_if_t<isAttacking, Q> >
    Citizen(T health, T age, T attackPower) : health_(health), age_(age), attackPower_(attackPower) { assert(age >= lower && age <= upper); };

    T getHealth() { return health_; }
    T getAge() { return age_; }
    void takeDamage(T damage) {  health_ = health_ >= damage ? health_ - damage : 0; }

    bool isAlive() { return health_ > 0; }

    /**
     * Return attack power (enabled only for sheriff).
     */
    template <typename Q = T, typename = typename std::enable_if_t<isAttacking, Q> >
    T getAttackPower()  { return attackPower_; }
};

template <typename T>
using Adult = Citizen<T, ADULT_MIN_AGE, ADULT_MAX_AGE, false>;

template <typename T>
using Teenager = Citizen<T, TEEN_MIN_AGE, TEEN_MAX_AGE, false>;

template <typename T>
using Sheriff = Citizen<T, ADULT_MIN_AGE, ADULT_MAX_AGE, true>;


#endif //HORROR_CITIZEN_H
