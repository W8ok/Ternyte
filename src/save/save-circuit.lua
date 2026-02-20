-- save/save-circuit.lua
local file = assert(io.open("saves/circuit.racc", "w"))

-- Formatting
local function write_count(label, value)
  file:write(string.format("%s:\t%s\n", label, value))
end

-- Version control
file:write(string.format("%s\t%s\n\n", name, version))

-- Count values
write_count("Gate Count", gate_count)
write_count("Wire Count", wire_count)

file:write("\n")

-- Gate values
local rotation_names = {"Right", "Down", "Left", "Up"}
local type_names = {"NOT", "AND", "OR", "XOR"}

for i, gate in ipairs(gates) do
  local input_str = ""
  if gate.input_idx then
    input_str = table.concat(gate.input_idx, ", ")
  end

  file:write(string.format(
    "Gate %d:\t(%d, %d), rot=%s, type=%s, output=%d, inputs=[%s]\n",
    i, gate.x, gate.y,
    rotation_names[gate.rotation + 1],
    type_names[gate.type + 1],
    gate.output_idx,
    input_str
  ))
end

file:write("\n")

-- Wire values
for i, wire in ipairs(wires) do
  file:write(string.format(
    "Wire %d:\t(%d, %d), (%d, %d), [conn: %d]\n",
    i, wire.x1, wire.y1, wire.x2, wire.y2, wire.connection_idx
  ))
end

file:close()
