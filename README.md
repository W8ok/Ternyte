# Ternyte - My (hopefully) actually useful passion project

I was looking for a good ternary logic simulator but couldn't find anything that fit my needs.  
So i decided to try and make my own.  
  
**Current Status**: In active development and will likely not be useable for a few weeks at least.  

## Goals

Goals obviously change over time so the initial goals might be very different from future goals.

### Inital Goals
* **The basics** - A simple expandable logic simulator with binary and ternary logic in primary focus.  
* **Chip making** - The ability to combine logic gates together to make a "chip" in a hierarchical structure.  
* **Save data** - The program should have a save function to save chips made and the project as a whole.  
* **Intuitive GUI** - The program shouldn't require any manual to use nor should it be annoying to use.  

### Aspirational Goals (Currently not achievable but maybe one day)
* A builtin algorithm to calculate a logic diagram from a truth table from selected gates.  
* Arbitrary sized buslines and gate input counts.  
* Advanced GUI to allow for greated user specific configuration while remaining easy and intuitive to use.  
* Integrate binary and ternary gates to allow for them both to be used in a single circuit.  

## Roadmap
[x] **Foundational progress** - Get a basic terminal interface working with the core logic functions  
[] **GUI** - Get a GUI working and basic drawing capabilities  
[] **Binary** - Implement all binary logic gates  
[] **Ternary** - Implement the basic and most universal of ternary logic gates  
[] **Persistance** - Save data and project seperation  
[] **Hierachical design** - Allow for hierarchical chip making  
  
Currently in active development thus the roadmap will be subject to active change.  

## Dev Log / Notes
**04/01/2026** - The project is started and so far the autism powers the motivation to continue. The core of the project has been organized and a few of the different logic gates are made and tested. Next step is to get working on some form of GUI, im thinking either raylib or SDL2/3.  
**05/01/2026** - I tried out SDL3, but it refused to work. I assume the issue is wayland related but i'm not sure. Raylib worked fine, so thats what the project will use i suppose. Got the GUI foundation up and running and currently working on drawing "wires" to the workspace.  
