## Algorithm Draft Sheet / Ideas

This is a collection of ideas for how certain systems, especially saving and performance optimizations, could be implemented. Mostly for future reference and brainstorming.  
The sheet is intentionally loose; ideas are meant to be grab-and-go for future-me. Some are simple, some are overkill, some might never get used. But it’s good to have a reference when implementing complex systems.  

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
