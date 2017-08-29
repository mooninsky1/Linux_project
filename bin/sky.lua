--[[
测试c++向lua传递数值
print("c++ nValue="..nValue)
--]]

--[[
调用c++函数
local sum = AddSum(5,7)
print("sum is:"..sum)
--]]

--[[
lua define function
--]]

local test  = function ( ... )
	-- body
	print("this is one kind of lua's fun")
end

function fun( ... )
	-- body
	print("this is nother lua's fun")
end

test()

fun()

--[[
this functions call by c/c++
--]]
function C_Call_Lua( a,b )
	-- body
	local sum = a+b
	print("in lua sum is:"..sum)
	return sum
end