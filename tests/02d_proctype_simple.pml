int globalTime = 0;

proctype clock() {
    do
    :: globalTime++
    od
}
