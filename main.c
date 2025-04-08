#include "defs.h"

int main(int argc, char *argv[])
{
    int numRuns;
    DequeType piratesDequeArr[NUM_SCENARIOS];
    FighterType *torts[NUM_SCENARIOS];
    FighterType *hares[NUM_SCENARIOS];
    StatsType  statsArr[NUM_SCENARIOS];
    RunSpecsType *RunSpecsArr[NUM_SCENARIOS];


    if(argc < 2){
        numRuns = NUM_RUNS;
    }
    else{
        numRuns = atoi(argv[1]);
    }

    srand( (unsigned)time( NULL ) );

    initStats(statsArr);


    for(int i=0; i<numRuns; ++i){

        initRun(hares, torts, piratesDequeArr);
        initRunsSpecsArray(hares, torts, piratesDequeArr, statsArr, RunSpecsArr);

        pthread_t st1, st2, st3;
        pthread_create(&st1, NULL, scenarioThread, RunSpecsArr[0]);
        pthread_create(&st2, NULL, scenarioThread, RunSpecsArr[1]);
        pthread_create(&st3, NULL, scenarioThread, RunSpecsArr[2]);

        pthread_join(st1, NULL);
        pthread_join(st2, NULL);
        pthread_join(st3, NULL);

        cleanUpRun(RunSpecsArr, hares, torts, piratesDequeArr);

    }

    printStats(RunSpecsArr[0]->stats, RunSpecsArr[1]->stats, RunSpecsArr[2]->stats, numRuns);


}

/*
  Function:  randm
  Purpose:   returns a pseudo randomly generated number, 
             in the range 0 to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1) 
*/
int randm(int max)
{
  double r = ( (double)rand() / ((double)(RAND_MAX)+(double)(1)) ); 
  return (int)(r * max);
}

/*
  Function:  randmRange
  Purpose:   returns a pseudo randomly generated number, 
             in the range min to max, inclusively
       in:   lower end of the range of the generated number
            upper end of the range of the generated number
   return:   randomly generated integer in the range [min, max]
*/

int randmRange(int min, int max)
{
  return min + randm(max - min + 1);
}



