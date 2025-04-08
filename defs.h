#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define C_OK       0
#define C_NOK     -1

#define NUM_RUNS       100
#define NUM_PIRATES     10
#define NUM_SCENARIOS    3

#define TORT_STRENGTH    5
#define TORT_ARMOUR      8
#define HARE_STRENGTH    8
#define HARE_ARMOUR      5
#define HERO_HEALTH     20
#define PIRATE_HEALTH   10
#define SWORD_STRENGTH   2

#define MAX_STR         64

typedef enum { SUCCESS, FAILURE, PART_SUCCESS, RES_UNKNOWN } ResultType;
typedef enum { FRONT, BACK } DirectionType;

typedef struct {	// Stats for one scenario, accumulated over all runs
  int numSuccess;
  int numPartSuccess;
  int numFailure;
} StatsType;

typedef struct {	// One fighter:  Tortoise, Hare, or Pirate
  int  strength;
  int  armour;
  int  health;
} FighterType;

typedef struct Node {
  FighterType  *data;
  struct Node  *next;
} NodeType;

typedef struct {	// Stores the fighting pirates for one scenario
  NodeType *head;
  NodeType *tail;
} DequeType;

typedef struct {	// Specs for one scenario of one run
  DequeType   *pirates;
  FighterType *tort;
  FighterType *hare;
  StatsType   *stats;
} RunSpecsType;

typedef struct {	// Specs for one fight of one scenario of one run
  FighterType  *hero;
  DequeType    *pirates;
  DirectionType dir;
  sem_t        *dqMutex;
} FightSpecsType;


// main.c prototypes
int randm(int);
int randmRange(int, int);


// deque.c prototypes
void initDeque(DequeType *);
int addFighter(DequeType *, FighterType *);
int removeFighterFromFront(DequeType *, FighterType **);
int removeFighterFromBack(DequeType *, FighterType **);
int deepCopyDeque(DequeType *, DequeType *);
int checkEmptyDeque(DequeType *);
void cleanupDeque(DequeType *);


// fight.c prototypes
void initFight(FighterType *, DequeType *, DirectionType , sem_t * ,FightSpecsType **);
void initFightSpecs(RunSpecsType *, FightSpecsType **, FightSpecsType **);
void *fightThread(void* );
int mainFightLogic(FighterType *, FighterType *);
void pirateHitsHero(FighterType *, FighterType *); 
void heroHitsPirate(FighterType *, FighterType *);
int checkPirateIfDead(FighterType *);


// fighter.c prototypes
void initPirate(FighterType **);
int initPirates(DequeType *);
void initTortoise(FighterType **);
void initHare(FighterType **);
void deepCopyFighter(FighterType *, FighterType **);
int addSwordStrength(FighterType *);

// run.c prototypes

void initRunsSpecs(DequeType *, FighterType *, FighterType *, StatsType *, RunSpecsType **);
void initRunsSpecsArray(FighterType **, FighterType **, DequeType * ,StatsType *, RunSpecsType **);
void initRun(FighterType **, FighterType **, DequeType *);
void *scenarioThread(void* );
void cleanUpRun(RunSpecsType **, FighterType **, FighterType **, DequeType *);


// stats.c prototypes
void initStats(StatsType *);
int computeScenarioOutcome(FightSpecsType *, FightSpecsType *);
int updateStats(ResultType , StatsType *);
void printStats(StatsType *, StatsType *, StatsType *, int);



#endif