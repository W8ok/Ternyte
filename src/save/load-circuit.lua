-- src/save/load-circuit.lua
local file = assert(io.open("saves/circuit.racc", "r"))

local function skip_empty_lines(file)
  local line
  repeat
    line = file:read("*line")
  until line and line:match("%S")
  return line
end

-- Read header
local first_line = file:read("*line")
if first_line then
  local n, v = first_line:match("([^\t]+)\t([^\t]+)")
  name = n or "Unknown"
  version = v or "0.0.0"
end

-- Read Gate and Wire counts
local gate_count_line = skip_empty_lines(file)
local wire_count_line = skip_empty_lines(file)
gate_count = tonumber(gate_count_line:match("%d+")) or 0
wire_count = tonumber(wire_count_line:match("%d+")) or 0

-- Read Gates
local rotation_map = {Right=0, Down=1, Left=2, Up=3}
local type_map     = {NOT=0, AND=1, OR=2, XOR=3}

gates = {}
for i = 1, gate_count do
  local line = skip_empty_lines(file)
  if line then
    -- Parse the line
    local x, y, rot_str, type_str, output_idx, inputs_str =line:match(
      "%((%d+),%s*(%d+)%)%s*,%s*rot=([%w]+),%s*type=([%w]+),%s*output=(%d+),%s*inputs=%[(.-)%]"
      -- Dont ask... idk
    )
    -- Convert input string to numbers
    local input_idx = {}
    for num in inputs_str:gmatch("%d+") do
      table.insert(input_idx, tonumber(num))
    end

    gates[i] = {
      x = tonumber(x),
      y = tonumber(y),
      rotation = rotation_map[rot_str] or 0,
      type = type_map[type_str] or 0,
      output_idx = tonumber(output_idx),
      input_idx = input_idx
    }
  end
end

-- Read Wires
wires = {}
for i = 1, wire_count do
  local line = skip_empty_lines(file)
  if line then
    local x1, y1, x2, y2, connection_idx = line:match(
      "%((%d+),%s*(%d+)%)%s*,%s*%((%d+),%s*(%d+)%)%s*,%s*%[conn:%s*(%d+)%]"
      -- Dont ask... idk
    )
    wires[i] = {
      x1 = tonumber(x1),
      y1 = tonumber(y1),
      x2 = tonumber(x2),
      y2 = tonumber(y2),
      connection_idx = tonumber(connection_idx)
    }
  end
end

file:close()
