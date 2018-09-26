import numpy as np 
from numpy.linalg import inv

#创建矩阵

#使用numpy第一种方式创建矩阵 使用matrix类
#但是matrix类 不是numpy推荐的 应主要学习numpy的array类
# 这里注意 参数的格式 [[1,2],[3,4],[5,6]]
A = np.matrix([[1,2],[3,4],[5,6]])

print("矩阵类A:{0}".format(A))

C = np.matrix('1,2,7;3,4,8;5,6,9')
print("矩阵类C:{0}".format(C))


#第二种方式创建矩阵 这里 矩阵元素
#注意参数的格式
B = np.array(range(1,7)).reshape(3,2)
print("矩阵B:{0}".format(B))


#这里注意矩阵运算两个矩阵相乘的问题
#第一 如果是matrix类创建的矩阵 矩阵相乘需要 按照线性代数矩阵相乘的原则进行
#线性代数  矩阵相乘 
#第二 如果是array创建的矩阵 这里需要注意 两个矩阵相乘按照哈达玛乘积原则进行
'''
需要注意的是，两个矩阵的标准乘积不是指两个矩阵中对应元素的乘积。
不过， 那样的矩阵操作确实是存在的，
被称为元素对应乘积 (element-wise product) 
或者哈 达玛乘积 (Hadamard product)，
'''

D = B*B

print('矩阵的哈达玛乘积:{0}'.format(D))


#在线性代数中一些特殊矩阵 单位矩阵 对角矩阵 上三角与 下三角矩阵

#生成特殊矩阵 3行两列的 零矩阵
A = np.zeros((3,2))
print('零矩阵:{0}'.format(A))
#生成特殊矩阵 单位矩阵 3行3列
B = np.identity(3)
print('单位矩阵:{0}'.format(B))

#生成特殊矩阵 对角矩阵 

C = np.diag([1,2,3])

print('对角矩阵:{0}'.format(C))


#矩阵中向量的提取

m = np.array(range(1,10)).reshape(3,3)
print('矩阵m:{0}'.format(m))
#提取行向量

p = m[[0,2]]

print('提取矩阵的指定行的行向量:{0}'.format(p))

#方法2
print('矩阵m:{0}'.format(m))
p = m[[True,False,True]]

print('提取矩阵的指定行的行向量2:{0}'.format(p))

#提取列向量

l = m[:,[1,2]]

print('列向量:{0}'.format(l))

l = m[:,[False,True,True]]

print('列向量:{0}'.format(l))



#矩阵的运算 矩阵相加减  矩阵与数字的乘积


n = np.array(range(1,5)).reshape(2,2)

print('矩阵n:{0}'.format(n))


#矩阵的转置
np.transpose(n)
p = np.transpose(n)

print('矩阵n转置:{0}'.format(n))
print('矩阵n转置结果:{0}'.format(p))

r = n + n


print('矩阵加运算:{0}'.format(r))

r = n - n

print('矩阵减运算:{0}'.format(r))

#矩阵与数字的乘积

r = 3*n

print('矩阵与数字的乘积:{0}'.format(r))


#矩阵的哈达玛乘积

p = n*n

print('矩阵的哈达玛乘积:{0}'.format(p))

#矩阵的线性代数乘法

p = n.dot(n)

print('矩阵的乘法:{0}'.format(p))


#矩阵的逆矩阵

p = inv(n)


print('矩阵的逆:{0}'.format(p))




