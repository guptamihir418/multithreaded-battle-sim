#include "defs.h"

/*
  Function:  initRunsSpecs
  Purpose:   initialize one strcture of runSpecs
       in:   pointer to deque of pirates, pointer to two heroes,
             pointer to statsType, double pointer to one structure of runSpecs
       out:  pointer to the initialized structure of runSpecs
   return:   Nothing
*/
void initRunsSpecs(DequeType *pirates, FighterType *hare, FighterType *tort, StatsType *stats, RunSpecsType **run){

    *run = malloc(sizeof(RunSpecsType));
    (*run)->pirates = pirates;
    (*run)->hare = hare;
    (*run)->tort = tort;
    (*run)->stats = stats;

}


/*
  Function:  initRunsSpecsArray
  Purpose:   initializes an array of runSpecs
       in:   double pointer to the array of hares, tortoises, stats and 
             pointer to array of Pirate Deques, double pointer to array of runSpecs
       out:  pointer to the initialized array of runSpecs
   return:   Nothing
*/
void initRunsSpecsArray(FighterType **hares, FighterType **tortoises, DequeType *pirDeqs ,StatsType *stats, RunSpecsType **runs){

    for(int i=0; i<NUM_SCENARIOS; ++i){
        initRunsSpecs(&pirDeqs[i], hares[i], tortoises[i], &stats[i], &runs[i]);
    }

}


/*
  Function:  initRun
  Purpose:   initialize the arrays of hares, tortoises and pirates deque
       in:   double pointer to the array of hares, tortoises and 
             pointer to array of Pirate Deques
       out:  pointer to the initialized array of hares, tortoises and pirates deque
   return:   Nothing
*/
void initRun(FighterType **hares, FighterType **tortoises, DequeType *piratesDequeArr){

    
    initDeque(&piratesDequeArr[0]);

    if(initPirates(&piratesDequeArr[0]) == C_NOK){
        printf("Error: pirates not initialized\n");
        return;
    }

    for(int i=1; i<NUM_SCENARIOS; ++i){
        initDeque(&piratesDequeArr[i]);
        deepCopyDeque(&piratesDequeArr[0], &piratesDequeArr[i]);
    }

    for(int i=0; i<NUM_SCENARIOS; ++i){
        initHare(&hares[i]);
        initTortoise(&tortoises[i]);

        if(i == 1){
            addSwordStrength(hares[i]);
        }
        if(i == 0){
            addSwordStrength(tortoises[i]);
        }
    }
}


/*
  Function:  scenarioThread
  Purpose:   calls the fight threads for each scenario
       in:   void ppointer to one scenario, which is typecasted to a RunSpecsType
       out:  Nothing
   return:   Nothing
*/ 
void *scenarioThread(void* arg){

    RunSpecsType *run = (RunSpecsType*)arg;

    pthread_t ft1, ft2;
    FightSpecsType *f1, *f2;
    ResultType r;

    initFightSpecs(run, &f1, &f2);

    pthread_create(&ft1, NULL, fightThread, f1);
    pthread_create(&ft2, NULL, fightThread, f2);
    pthread_join(ft1, NULL);
    pthread_join(ft2, NULL);

    r = computeScenarioOutcome(f1, f2);

    // update the stats of this scenario
    updateStats(r, run->stats);

    // free the memory allocated for the fightSpecs
    free(f1);
    free(f2);

}

/*
  Function:  cleanUpRun
  Purpose:   cleans up all the allocated memory for the run
       in:   pointer to the array of hares, tortoises and pirates deque
       out:  Nothing
   return:   Nothing
*/
void cleanUpRun(RunSpecsType **arr, FighterType **hares, FighterType **tort, DequeType *deques){

    for(int i=0; i<NUM_SCENARIOS; ++i){
        free(hares[i]);
        free(tort[i]);
        cleanupDeque(&deques[i]);
        free(arr[i]);
    }
   
}