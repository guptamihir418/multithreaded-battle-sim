#include "defs.h"   

/*
  Function:  initStats
  Purpose:   initialize the statistics for NUM_SCENARIOS
       in:   pointer to the stats structure array
       out:  populated stats structure array
   return:   Nothing
*/
void initStats(StatsType *s){

    for(int i=0; i<NUM_SCENARIOS; ++i){
        s[i].numFailure = 0;
        s[i].numSuccess = 0;
        s[i].numPartSuccess = 0;
    }
}

/*
  Function:  computeScenarioOutcome
  Purpose:   compute the outcome of a scenario
       in:   pointer to two fightSpecs structures
       out:  nothing
   return:   ResultType for every different case
*/
int computeScenarioOutcome(FightSpecsType* f1, FightSpecsType *f2){

    if(f1->hero->health > 0 && f2->hero->health > 0){
        return SUCCESS;
    }
    if(f1->hero->health > 0 || f2->hero->health > 0){
        return PART_SUCCESS;
    }
    else{
        return FAILURE;
    }
    printf("Error: computeScenarioOutcome\n");
    return RES_UNKNOWN;
}

/*
  Function:  updateStats
  Purpose:   update the statistics for one scenario by comparing the results
       in:   ResultType, pointer to the statsType that needs to be updated
       out:  updated statsType values
   return:  C_OK if successful, C_NOK if not
*/
int updateStats(ResultType r, StatsType *s){

    if(r == SUCCESS){
        s->numSuccess++;
        return C_OK;
    }
    else if(r == PART_SUCCESS){
        s->numPartSuccess++;
        return C_OK;
    }
    else if(r == FAILURE){
        s->numFailure++;
        return C_OK;
    }
    return C_NOK;
}

/*
  Function:  printStats
  Purpose:   prints the result accumulated over the "n" runs
       in:   three pointers to statsType structures, and an int for the number of runs
       out:  output printed
   return:  nothing
*/
void printStats(StatsType *s1, StatsType *s2, StatsType *s3, int NumRuns){ // s1 -> tortoise with sword, s2 -> hare with sword, s3 -> None

    float div = (float)NumRuns/NUM_RUNS;

    printf("\n");

    printf("+--------------------------------------------------------------+\n");
    printf("| Hero with Sword | Perc Success | Perc Partial | Perc Failure |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("|    Tortoise     |     %02.0f       |     %02.0f       |     %02.0f       |\n", (s1->numSuccess)/div, (s1->numPartSuccess)/div, (s1->numFailure)/div);
    printf("+--------------------------------------------------------------+\n");
    printf("|    Hare         |     %02.0f       |     %02.0f       |     %02.0f       |\n", (s2->numSuccess)/div, (s2->numPartSuccess)/div, (s2->numFailure)/div);
    printf("+--------------------------------------------------------------+\n");
    printf("|    None         |     %02.0f       |     %02.0f       |     %02.0f       |\n", (s3->numSuccess)/div, (s3->numPartSuccess)/div, (s3->numFailure)/div);
    printf("+--------------------------------------------------------------+\n");

    printf("\nTotal Runs: %d\n", NumRuns);

}