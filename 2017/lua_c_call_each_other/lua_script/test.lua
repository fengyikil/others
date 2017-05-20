--测试c调用lua函数
function test_add(a,b) 
 return a+b
end

--测试c调用lua函数:这里比较绕，c调用 lua的test_c_lua_multi函数，而这个函数里面又调用了c注册到lua的函数lua_test
function test_c_lua_multi(a,b)
   res = lua_test(a,b) 
   return res;
end

--测试c调用lua函数:测试返回字符串
function test_return_str()
 return "booooooooooooming"
 end

--测试c调用lua函数:测试多参数输入和多参数返回
function test_more_in_out(a,b,c,d,e)
  return a,b,c,d,e
end

print("hello")
print("hello")
print("hello")
--测试lua调用c函数：返回多个参数
a,b,c,d=lua_test2(8,9)
print(type(a))
print(type(b))
print(type(c))
print(type(d))
--测试lua调用c函数：返回table
tab = lua_res_table();
print(type(tab))
for key,value in pairs(tab) do
 print(key,"is",value)
end