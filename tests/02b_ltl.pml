ltl NonTerm  { [] !final }
ltl Fin { <> final }
ltl OverTime { [] (final -> (globalTime > Tmin)) }
ltl Sum6 { [] (final -> ( aoutput == 6 )) }