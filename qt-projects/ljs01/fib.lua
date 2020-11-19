-- フィボナッチ数
function fib(n)
    if n < 2 then
        return n
    else
        return fib(n - 2) + fib(n - 1)
    end
end

n = tonumber(arg[1])
print(fib(n))

--[[
example
    lua fib_lua.lua 39
    luajit fib_lua.lua 39
--]]
