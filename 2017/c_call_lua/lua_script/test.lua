--����c����lua����
function test_add(a,b) 
 return a+b
end

--lua_testΪcע�ᵽlua�ĺ���
function test_c_lua_multi(a,b)
   res = lua_test(a,b) 
   return res;
end


function test_return_str()
 return "booooooooooooming"
 end

function test_more_in_out(a,b,c,d,e)
  return a,b,c,d,e
end

print("hello")
print("hello")
print("hello")