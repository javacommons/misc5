function real_print_recursive (e, level)
    local et = type(e)
    if et == 'table' then
        io.write("{ ")
        local iters = 0
        for k, v in pairs(e) do
            if iters ~= 0  then
                io.write(", ")
            end
            real_print_recursive(k, level + 1)
            io.write(": ")
            real_print_recursive(v, level + 1)
            iters = iters + 1
        end
        io.write(" }")
    elseif et == 'string' then
        io.write('"')
        io.write(e)
        io.write('"')
    else
        io.write(tostring(e))
    end
    if level == 0 then
        io.write("\n")
    end
end

function print_recursive (e)
    real_print_recursive(e, 0)
end
