--����c����lua����
function test_add(a,b) 
 return a+b
end

--����c����lua����:����Ƚ��ƣ�c���� lua��test_c_lua_multi��������������������ֵ�����cע�ᵽlua�ĺ���lua_test
function test_c_lua_multi(a,b)
   res = lua_test(a,b) 
   return res;
end

--����c����lua����:���Է����ַ���
function test_return_str()
 return "booooooooooooming"
 end

--����c����lua����:���Զ��������Ͷ��������
function test_more_in_out(a,b,c,d,e)
  return a,b,c,d,e
end

print("hello")
print("hello")
print("hello")
--����lua����c���������ض������
a,b,c,d=lua_test2(8,9)
print(type(a))
print(type(b))
print(type(c))
print(type(d))
--����lua����c����������table
tab = lua_res_table();
print(type(tab))
for key,value in pairs(tab) do
 print(key,"is",value)
end