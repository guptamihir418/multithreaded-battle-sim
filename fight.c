#include "defs.h"

/*
  Function:  initFightSpecs
  Purpose:   allocated the memory for two fights and initializes them
       in:   pointer to the runSpecs (one scenario)
       out:  pointer to two the fightSpecs structures
   return:   nothing
*/
void initFightSpecs(RunSpecsType *s, FightSpecsType **f1, FightSpecsType **f2){

    sem_t mutexDq;

   if(sem_init(&mutexDq, 0, 1) < 0){
        printf("Error initializing mutex\n");
        exit(1);
    }

   *f1 = malloc(sizeof(FightSpecsType));

    (*f1)->hero = s->tort;
    (*f1)->pirates = s->pirates;
    (*f1)->dir = FRONT;
    (*f1)->dqMutex = &mutexDq;

    *f2 = malloc(sizeof(FightSpecsType));

    (*f2)->hero = s->hare;
    (*f2)->pirates = s->pirates;
    (*f2)->dir = BACK;
    (*f2)->dqMutex = &mutexDq;
     

}
/*
  Function:  fightThread
  Purpose:   thread used by scenario threads to conduct fights
       in:   void pointer to fight, which is type casted to FightSpecsType pointer
       out:  nothing
   return:   nothing
*/
void *fightThread(void* arg){

    FightSpecsType *fight = (FightSpecsType *) arg;

    while(fight->hero->health > 0 && checkEmptyDeque(fight->pirates) == C_NOK){

        if(sem_wait(fight->dqMutex) < 0){
            printf("Error waiting on mutex\n");
            exit(1);
        }

        if(fight->dir == FRONT){
            FighterType *p;
            if(removeFighterFromFront(fight->pirates, &p) == C_OK){
                if(sem_post(fight->dqMutex) < 0){
                    printf("Error posting mutex\n");
                    exit(1);
                }
                if(mainFightLogic(fight->hero, p) == C_OK){}
            }
        }
        else if(fight->dir == BACK){
            FighterType *p;
            if(removeFighterFromBack(fight->pirates, &p) == C_OK){
                if(sem_post(fight->dqMutex) < 0){
                    printf("Error posting mutex\n");
                    exit(1);
                }
                if(mainFightLogic(fight->hero, p) == C_OK){}
            }
        }
        usleep(1000);
    }
}

/*
  Function:  mainFightLogic
  Purpose:   real fight is conducted here, conducts fight between pirate and hero
       in:   pointer to hero and pointer to pirate
       out:  nothing
   return:   C_OK if fight is over, C_NOK if while loop is broken ( which is never )
*/
int mainFightLogic(FighterType *hero, FighterType *pirate){

    while(1){

        heroHitsPirate(hero, pirate);

        if(pirate->health <= 0){
            pirate->health = 0;
            // free the pirate which is dead
            free(pirate);
            hero->health += 3;

            if(hero->health >= HERO_HEALTH){
                hero->health = HERO_HEALTH;
            }
            return C_OK;
        }

        pirateHitsHero(hero, pirate);
        if(hero->health <= 0){
            hero->health = 0;
            // if hero is dead, free the pirate
            free(pirate);
            
            return C_OK;
        }
    }

    return C_NOK;

}

/*
  Function:  pirateHitsHero
  Purpose:   calculates the damage done by the pirate to the hero, and changes the health of hero
       in:   pointer to hero and pointer to pirate
       out:  nothing
   return:   Nothing
*/

void pirateHitsHero(FighterType *hero, FighterType *pirate){

    int damage, tempStrength;

    tempStrength = randmRange(0, ((pirate)->strength - 2));
    tempStrength += (pirate)->strength;
    damage = tempStrength - (hero)->armour;

    if(damage <= 0){
        damage = 0;
    }

    (hero)->health -= damage;
}

/*
  Function:  heroHitsPirate
  Purpose:   calculates the damage done by the hero to a pirate, and changes the health of pirate
       in:   pointer to hero and pointer to pirate
       out:  nothing
   return:   Nothing
*/
void heroHitsPirate(FighterType *hero, FighterType *pirate){

    int damage;

    damage = (hero)->strength - (pirate)->armour;
    if(damage < 0){
        damage = 0;
    }

    (pirate)->health -= damage;
}
