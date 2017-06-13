# Malloc debugging flags for widelands on OSX / BSD Library malloc

export MallocGuardEdges=yes
export MallocScribble=yes
export MallocCheckHeapStart=1 # stat checking immdiately
export MallocCheckHeapEach=100 # cehck every 100th malloc - sloooow
# export MallocCheckHeapSleep=36000 # wait ten minutes for a debugger to attach
export MallocCheckHeapAbort=1
export MallocErrorAbort=yes
export MallocCorruptionAbort=yes  
