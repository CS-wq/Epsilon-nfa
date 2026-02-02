Explanation of the Program

      Objective

The objective of this program is to transform a Non-Deterministic Finite Automaton (NFA) with ε-transitions into an equivalent NFA without ε-transitions, while preserving the recognized language.

      Data Structures

The automaton is represented using:

Arrays to store the number of states, symbols, start state, and final states.

A matrix eps to represent ε-transitions.

A 3D array trans to represent symbol transitions.

An eclosure matrix to store the ε-closure of each state.

newTrans and newFinal to represent the resulting NFA without ε-transitions.

      ε-Closure Computation

The function dfsEpsilon() performs a depth-first search to find all states reachable from a given state using only ε-transitions.
The function computeEclosures() applies this process to every state to compute its ε-closure.

       Construction of New Transitions

The function computeNewTransitions() constructs the transition table of the new NFA:

For each state p and input symbol,

All states reachable from any state in ε-closure(p) by that symbol are collected,

Their ε-closures are added as reachable states.

Thus, all ε-transitions are eliminated.

       Determination of Final States

The function computeNewFinalStates() determines final states of the new NFA.
A state is marked as final if at least one state in its ε-closure is a final state in the original NFA.

         Output

The function displayNewNFA() prints:

The final states of the new NFA

The transition function without ε-transitions

Conclusion

This program correctly removes ε-transitions from an NFA by using ε-closures, resulting in an equivalent NFA without ε-moves, suitable for further automata processing
