# Front end
The frontend is the user interface for creating a statemachine.

## ROW
Each type of row has a specialisation based on what functionality is defined for it.
The row receives a tag based on what features it has.
To disable a parameter pass MSM::Front::None.  
Defining a row with the same origin state and event is possible, the guards will be checked in the order that they are defined. The first transition with a satisfied guard will be executed.

### Normal transition
A normal transitions state if guard is statisfied.
If an action is provided it will be executed in between the on_exit of the Origin state and the on_entry of the target state.

**A normal transition without action or guard**  
`Row<Origin, Event, Target, none, none>`

**A normal transition without guard**  
`Row<Origin, Event, Target, Action, none>`

**A normal transition without action**  
`Row<Origin, Event, Target, none, Guard>`

### Internal transition
An internal transition does not transition state but does execute an Action if the guard is satisfied.

**An internal transition without guard**  
`Row<Origin, Event, none, Action, none>`

**An internal transition without action**  
`Row<Origin, Event, none, Action, Guard>`

### Empty transition
Empty transtitions can be used to ignore events either always or only if the guard is satisfied.

**An empty transition with guard**  
`Row<Origin, Event, none, none, Guard>`

**An empty transition**  
`Row<Origin, Event, none, none, none>`

## Methods
Rows define the static functions for executing an action or a guard if available.
```C++
template<class OriginState, class Event, class TargetState, class Action, class Guard>
template <class Fsm>
static void TTRow<OriginState, Event, TargetState, Action, Guard>::ExecuteAction(Fsm& fsm, const Event& evt, TargetState& tgs);

template<class OriginState, class Event, class TargetState, class Action, class Guard>
template <class Fsm>
static bool TTRow<OriginState, Event, TargetState, Action, Guard>::ExecuteGuard(Fsm& fsm, const Event& evt, TargetState& tgs);
```
