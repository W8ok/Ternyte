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

---

## Roadmap

[x] **Foundation setup** - Project restarted, SDL3 selected, and initial data structures designed.  
[x] **Planning & restructuring** - Defined architecture for saving, logging, component placement, and future multithreaded autosaving.  
[] **Basic SDL3 rendering** - Draw grid, components, and wires, and implement keyboard/mouse interaction.  
[] **Save/load system** - Implement Lua-based serialization, version checks, and backup system.  
[] **Terminal interface** - Implement terminal commands for placing components and wires on a grid.  
[] **Error handling & logging** - Complete panic/logging system, including cycle logging and archive management.  
[] **Binary logic gates** - Implement all standard binary gates for testing and usage.  
[] **Ternary logic gates** - Implement core ternary gates.  
[] **Advanced GUI features** - Zoom, selection, drag-and-drop, component menus likely made along side a custom GUI library.  
[] **Hierarchical design** - Enable chip creation and combination.  
[] **Autosave optimization** - Contiguous memory layout and multithreaded snapshot copying.

---

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

---

## Algorithm Draft Sheet / Ideas

This is a collection of ideas for how certain systems, especially saving and performance optimizations, could be implemented. Mostly for future reference and brainstorming.  
The sheet is intentionally loose; ideas are meant to be grab-and-go for future-me. Some are simple, some are overkill, some might never get used. But it’s good to have a reference when implementing complex systems.  

---

### Save System / Snapshots
* **Flat array arena copy**
  - Keep all components/wires in contiguous arrays.
  - Save by iterating over arrays and copying them into a buffer sequentially.
  - Benefits: cache-friendly, fast memory access, easy to multithread.
  - Future: batch memory copy in chunks, maybe 64-bit or SIMD style.

* **Multithreaded save**
  - Divide snapshot array into chunks.
  - Assign each chunk to a worker thread to copy/serialize independently.
  - Main thread waits for workers to finish before finalizing save.
  - Could integrate Lua serialization calls inside each thread for independent scripting.

* **GPU-accelerated memory copy**
  - If buffer becomes very large, use GPU memcpy (e.g., Vulkan/compute shaders) to offload the copy.
  - Likely overkill for now but noted as future optimization.

* **Incremental/delta saves**
  - Track which components/wires changed since last save.
  - Only copy/serialize modified chunks to reduce save time.
  - Could integrate with multithreaded arena copy.

* **Autosave queue**
  - Maintain 3 autosave slots + main save + previous main save.
  - Autosave copies data to buffer first, then worker thread handles serialization.
  - If worker threads busy, new autosave waits or overwrites oldest autosave buffer.

* **Version-aware save**
  - Include x.y.z version metadata in save.
  - X = incompatible / major rewrite → reject old saves
  - Y = major change → migration scripts
  - Z = minor → ignored for compatibility
  - Use Lua for migration scripts.

---

### Event-Driven Rendering / “Only Render When Needed”

To maximize performance and reduce unnecessary CPU/GPU usage, Ternyte will use **event-driven rendering**, only redrawing the screen when something has actually changed.

**Key Ideas**:
* **Dirty flag system** – A boolean flag tracks whether the screen needs updating. Any user action or state change sets this flag.
* **Selective rendering** – Only the components, wires, or regions that changed are redrawn. No full-frame clears unless absolutely necessary.
* **Input-driven updates** – Rendering is triggered by input events (mouse, keyboard) or programmatic changes to the grid, components, or camera.
* **Logic-simulation mode** – When the full logic simulation is active, continuous updates are enabled, but still controlled by a flag to prevent unnecessary rendering when paused.

**Benefits**:
* Reduced CPU/GPU usage, especially on older machines or systems without dedicated graphics.
* Avoids unnecessary frame clearing and redraws, keeping performance smooth.
* Makes the rendering system modular, allowing easy integration with camera, grid, and future GUI features.

**Implementation Notes**:
* Maintain a `bool dirty` in the main app context.
* Whenever a visual change occurs: `dirty = true`.
* In the main loop or iterate function:

---

### Logging / Panic / Debug
* **Cycle-based logging**
  - Every simulation cycle = one log line.
  - Include: action performed, affected component, data written.
  - Can separate C log vs Lua log.

* **Archival on crash**
  - If `SDL_APP_FAILURE` occurs, archive current log with timestamp.
  - Otherwise, overwrite temporary log (configurable max temp logs).

* **Minor panic / warnings**
  - Record non-critical events in log without aborting.
  - Footnotes for future debugging.

---

### Performance / Optimization Ideas
* **Contiguous memory layout**
  - Keep component/wire structs sequential for fast iteration.
  - Index-based references instead of pointers to allow easy copying.

* **Batch processing / arena-style memory**
  - When needed, implement arena buffer for save snapshots.
  - Could be used later for multithreaded updates or even logic propagation.

* **Thread pool**
  - Fixed number of worker threads for background tasks:
    - Save/serialize
    - Log writing
    - Optional future simulations
  - If all threads busy, wait or queue tasks.

* **Partial updates**
  - Track “dirty” components/wires.
  - Only redraw or recalc logic where necessary.
  - Reduces CPU/GPU work per frame.

* **GPU-assisted operations (future)**
  - Could use GPU for:
    - Massive grid updates
    - Logic simulations for very large circuits
    - Memory copying for snapshots

---

### Miscellaneous / Experimental Ideas
* **Terminal-first interface**
  - Early version: all placement and wiring via typed commands.
  - Helps focus on data structures before full GUI.

* **Hierarchical indexing**
  - Components know their index in flat array + optional area ID.
  - Could later implement zones/areas for optimized batch updates.

* **Simulation pipelining**
  - Separate threads for:
    - Input handling
    - Logic evaluation
    - Rendering
    - Autosave/log writing

* **Save optimization strategies**
  - Serialize in a format that’s easy for Lua to parse.
  - Could even store as JSON or binary, depending on complexity.
  - Optionally compress if saves get huge.
