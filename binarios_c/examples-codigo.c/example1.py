class A:
    def show(self):
        print("A")

class B(A):
    def show(self):
        print("B")

class C(A):
    def show(self):
        print("C")

class D(B, C):
    pass

D().show()

# Resposta:

# - *Vai imprimir *B
# - Python usa MRO (Method Resolution Order)
# - D herda de B, C → busca primeiro em B
