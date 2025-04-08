#include "defs.h"

/*
  Function:  initPirate
  Purpose:   initialize a pirate with randonly generated values as given in specifications
       in:   double pointer to a pirate
       out:  pointer to allocated pirate
   return:   nothing
*/
void initPirate(FighterType **pirate){

    *pirate = malloc(sizeof(FighterType));

    (*pirate)->strength = randmRange(5, 9);
    (*pirate)->armour = randmRange(1,4);
    (*pirate)->health = PIRATE_HEALTH;

}
/*
  Function:  initPirates
  Purpose:   popilates the deque with pirates
       in:   pointer to the deque
       out:  popukated deque with pirates
   return:   C_OK if successful, C_NOK if not
*/
int initPirates(DequeType *deque){

    if(checkEmptyDeque(deque) == C_NOK){
        return C_NOK;
    }

    for(int i=0; i<NUM_PIRATES; ++i){
        FighterType *pirate;
        initPirate(&pirate);
        addFighter(deque, pirate);
    }

    return C_OK;
}

/*
  Function:  initTortoise
  Purpose:   initialize the tortoise 
       in:   double pointer to a tortoise
       out:  pointer to allocated tortoise
   return:   nothing
*/
void initTortoise(FighterType **tortoise){
    
    *tortoise = malloc(sizeof(FighterType));

    (*tortoise)->strength = TORT_STRENGTH;
    (*tortoise)->armour = TORT_ARMOUR;
    (*tortoise)->health = HERO_HEALTH;

}
/*
  Function:  initHare
  Purpose:   initialize the hare 
       in:   double pointer to a hare
       out:  pointer to allocated hare
   return:   nothing
*/
void initHare(FighterType **hare){

    *hare = malloc(sizeof(FighterType));

    (*hare)->strength = HARE_STRENGTH;
    (*hare)->armour = HARE_ARMOUR;
    (*hare)->health = HERO_HEALTH;
}


/*
  Function:  deepCopyFighter
  Purpose:   copies all the values of a fighter to a new fighter
       in:   pointer to fighter to be copied, double pointer to new fighter
       out:  pointer to allocated new fighter
   return:   nothing
*/
void deepCopyFighter(FighterType *fighter, FighterType **copy){

    (*copy) = malloc(sizeof(FighterType));

    (*copy)->armour = fighter->armour;
    (*copy)->health = fighter->health;
    (*copy)->strength = fighter->strength;
}

/*
  Function:  addSwordStrength
  Purpose:   adds the strength of the sword to the fighter
       in:   pointer to fighter to be modified
       out:  nothing, fighter's strength is modified
   return:   C_OK if successful, C_NOK if not
*/
int addSwordStrength(FighterType *fighter){

    if(fighter == NULL){
        printf("Error: Fighter is NULL\n");
        return C_NOK;
    }

    fighter->strength += SWORD_STRENGTH;
    return C_OK;
}

