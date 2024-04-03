import numpy as np
import time

# 행렬 곱셈 연산을 수행하는 함수
def matrix_multiply_python(a, b):
    return np.dot(a, b)

# 행렬 생성
size = 10000
a = np.random.rand(size, size)
b = np.random.rand(size, size)

# 순수 Python으로 행렬 곱셈 수행
start_time = time.time()
result_python = matrix_multiply_python(a, b)
end_time = time.time()
python_execution_time = end_time - start_time
print("순수 Python으로 행렬 곱셈 수행 시간:", python_execution_time)