# Ternyte - My (hopefully) actually useful passion project

I was looking for a good ternary logic simulator but couldn't find anything that fit my needs.  
So I decided to try and make my own.  

**Current Status**: Restarted development with a proper plan and restructuring. Work has officially begun as of 07/02/2026, and the project will be actively developed using SDL3 as the main framework.

## Goals

Goals obviously change over time, so the initial goals might be very different from future goals.

### Initial Goals
* **Grid-based workspace** - Implement a grid system where components can be placed, connected, and manipulated.  
* **Terminal-driven commands** - For early development, a terminal interface to place gates, wires, and components without GUI distractions.  
* **Save/load system** - Save projects and circuit states reliably, with versioning, backups, and Lua-based scripting for serialization.  
* **Basic SDL3 GUI** - Render the grid and components using SDL3, support simple keyboard/mouse interactions, and allow wire placement and component selection.  
* **Error handling & logging** - Full panic and logging system for C and Lua operations to capture program state, save errors, and debug crashes.

### Aspirational Goals
* **Binary & ternary logic integration** - Support both logic systems in a single circuit.  
* **Hierarchical chip design** - Ability to create modular chips and combine them into larger circuits.  
* **Advanced autosave & snapshot optimization** - Contiguous memory copying and multithreaded autosaving for minimal stutter.  
* **Interactive GUI improvements** - Dragging, selection boxes, zooming, and intuitive component placement.  
* **Automatic truth table generation** - Algorithms to generate logic diagrams from selected truth tables.  
* **Large buses & variable input gates** - Arbitrary-sized connections and input counts for advanced circuit design.

## Roadmap

[x] **Foundation setup** - Project restarted, SDL3 selected, and initial data structures designed.  
[x] **Planning & restructuring** - Defined architecture for saving, logging, component placement, and future multithreaded autosaving.  
[] **Basic SDL3 rendering** - Draw grid, components, and wires, and implement keyboard/mouse interaction.  
[] **Save/load system** - Implement Lua-based serialization, version checks, and backup system.  
[] **Terminal interface** - Implement terminal commands for placing components and wires on a grid.  
[] **Error handling & logging** - Complete panic/logging system, including cycle logging and archive management.  
[] **Binary logic gates** - Implement all standard binary gates for testing and usage.  
[] **Ternary logic gates** - Implement core ternary gates.  
[] **Advanced GUI features** - Zoom, selection, drag-and-drop, component menus, likely made along side a custom GUI library.  
[] **Hierarchical design** - Enable chip creation and combination.  
[] **Autosave optimization** - Contiguous memory layout and multithreaded snapshot copying.

## Dev Log / Notes
**04/01/2026** - Original project started, core logic gates implemented, GUI exploration with Raylib began.  

**05/01/2026** - Attempted SDL3, ran into Wayland issues. Switched to Raylib and got basic GUI + wire drawing working.  

**06/01/2026** - Snapped wire drawing to grid, added selection and deletion logic, GUI mostly functional.  

**09/01/2026** - Wire mechanics polished, GUI considered complete for initial development phase.  

**07/02/2026** - Restarted project with proper planning and restructuring.  
- Decided to fully commit to **SDL3** as a system framework.  
- Wrote a complete plan for architecture: save system, logging, Lua integration, and future optimizations.  
- Starting fresh with a grid-based workspace and terminal-driven commands to build a solid foundation before adding logic, GUI features, and hierarchical design.  
- Today marks the new starting point: a structured, scalable approach with long-term maintainability in mind.
