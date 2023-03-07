#lang racket

;fib rekurencyjnie
(define (fib n)
    (if (< n 2) n 
        (+ (fib(- n 1)) (fib (- n 2)))
    )
)

(fib 4)

#|
A (fib 4) -> (fib 3) + (fib 2)
                B         C

B (fib 3) -> (fib 2) + (fib 1)
                D         E

D (fib 2) -> (fib 1) + (fib 0)
                F         G       

F (fib 1) -> 1
G (fib 0) -> 0
D (fib 2) -> 1 + 0 = 1
E (fib 1) -> 1

B (fib 3) -> D + E = 2
                   
C (fib 2) -> (fib 1) + (fib 0)
               H          I
H (fib 1) -> 1
I (fib 0) -> 0

C (fib 2) -> H + I = 1

A (fib 4) -> B + C = 2 + 1 = 3

dla kazdego n > 2 funkcja fib wywoluje kolejne funkcje (fib n -1) (fib n -2) az do n < 2 a nastepnie je sumuje
|#

;fib iteracyjnie
(define f0 0)
(define f1 1)

(define (fibI n)

    (define (it f0 f1 n)
        (if (= n 1) f1
            (it f1 (+ f0 f1) (- n 1))
        )
    )
        
    (it f0 f1 n)
)

(fibI 4)

#|
(fibI 4) -> (it 0 1 n = 4)
(it 1 (+ 0 1) 3)
(it 1 (+ 1 1) 2)
(it 2 (+ 2 1) 1) -> 3

sumuje kolejne elementy ciag fibonaciego#|