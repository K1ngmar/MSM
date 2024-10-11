# ROW
Eacc type of row has a specialisation based on what functionality is defined for it.
The row receives a tag based on what features it has.
To disable a parameter pass MSM::Front::None

**A normal transition without action or guard**  
`Row<Source,Event,Target,none,none>`

**A normal transition without guard**  
`Row<Source,Event,Target,Action,none>`

**A normal transition without action**  
`Row<Source,Event,Target,none,Guard>`

**An internal transition without guard**  
`Row<Source,Event,none,Action,none>`

**An internal transition without action**  
`Row<Source,Event,none,none,Guard>`

**An empty transition with guard**  
`Row<Source,Event,none,none,Guard>`

**An empty transition**  
`Row<Source,Event,none,none,none>`
