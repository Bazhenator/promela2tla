int Tmin = 20;

typedef twoDimArray { byte arr[128 / 64 * 2] };

twoDimArray barrierIn[1];

mtype : action = { done, stop, stopwarps, go, gowg, gowarp, donewarp };

byte globalMemory[128];
int aoutput = 100000;

chan workgroups = [16] of {int, bool};

twoDimArray isWarpReadyToRun[1];

int nWorkGroups = 0;
int workGroupSize = 0;
int tileSize = 0;