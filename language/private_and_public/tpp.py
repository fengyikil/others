class Man:
    __old=0
    def test(self):
        print(self.__old)
        man = Man()
        man.__old=5
        return man
    def getOld(self):
        return self.__old

newman=Man().test()
print(newman.getOld())

#直接访问报错
#print(newman.__old)

