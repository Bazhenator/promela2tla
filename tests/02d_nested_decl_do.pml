{
    do
    :: 1 ->
        atomic {
            sch_dev ? done;
            bool wgWaiting = true;
            do
            :: wgWaiting -> break
            od
        }
    od
}
