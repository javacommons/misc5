print(11+22)

local ffi = require("ffi")
ffi.cdef[[
void Sleep(int ms);
]]

function sleep(s)
  ffi.C.Sleep(s*1000)
end

for i=1,160 do
  io.write("."); io.flush()
  sleep(0.01)
end
io.write("\n")

local calc = ffi.load("calc")

ffi.cdef[[
const char *open_pipe_server(const char *prefix, const char *client, int show_client);
const char *open_pipe_client(const char *name);
const char *read_from_pipe(const char *hPipe);
void write_to_pipe(const char *hPipe, const char *s);
]]

-- local hPipe = calc.open_pipe_server("prefix", "json-cli.exe", 1)
local hPipe = ffi.string(calc.open_pipe_server("prefix", "json-cli.exe", 1))
print(ffi.string(hPipe))
calc.write_to_pipe(hPipe, "{\"name\": \"abc\", \"value\": 777}")
local json = calc.read_from_pipe(hPipe);
print(ffi.string(json))
