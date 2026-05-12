{
    atomic {
        for (d : 0 .. nWorkingDevices - 1) {
            for (u : 0 .. nWorkingUnitsPerDevice - 1) {
                barrierIn[d].arr[u] = 0
            }
        }
    }
}