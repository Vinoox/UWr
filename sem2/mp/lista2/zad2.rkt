#lang racket

;fib rekurencyjnie
(define (fib n)
    (if (< n 2) n 
        (+ (fib(- n 1)) (fib (- n 2)))))

(fib 4)

;(fib 4) -> (fib 3) + (fib 2)
;(fib 3) -> (fib 2) + (fib 1)
;(fib 2) -> (fib 1) = 1 + (fib 0) = 0
;(fib 3) -> 1 + (fib 1) = 1
;(fib 4) -> 2 + (fib 2) = 1 + 0
;(fib 4) -> 2 + 1 = 3
;dla kazdego n > 2 funkcja fib wywoluje kolejne funkcje (fib n -1) (fib n -2) az do n < 2 a nastepnie je sumuje


;fib iteracyjnie
(define f0 0)
(define f1 1)

(define (fibI n)

  (define (it f0 f1 n)
    (if (= n 0) f0
        (it f1 (+ f0 f1) (- n 1))))
        
    (it f0 f1 n))

(fibI 5)

;sumuje kolejne elementy ciag fibonaciego