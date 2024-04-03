import numpy as np
import ctypes
import time

# C 라이브러리 로드
lib = ctypes.CDLL('./matrix_multiply.so')  # .dll 파일을 사용할 경우 경로를 조정

# C 함수 프로토타입 정의
matrix_multiply = lib.matrix_multiply
matrix_multiply.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]

# 행렬 생성
size = 10000
a = np.random.rand(size, size)
b = np.random.rand(size, size)
result_c = np.zeros((size, size), dtype=np.float64)

# C로 행렬 곱셈 수행
start_time = time.time()
matrix_multiply(size, a.ctypes.data_as(ctypes.POINTER(ctypes.c_double)), b.ctypes.data_as(ctypes.POINTER(ctypes.c_double)), result_c.ctypes.data_as(ctypes.POINTER(ctypes.c_double)))
end_time = time.time()
c_execution_time = end_time - start_time
print("C로 행렬 곱셈 수행 시간:", c_execution_time)