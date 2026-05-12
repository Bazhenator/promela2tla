{
    do
    :: nempty(warps) ->
        warps ? warpId, instrId;
        instrId++
    :: empty(warps) ->
        sch_u ! 0, 0, stopwarps;
        break
    od
}