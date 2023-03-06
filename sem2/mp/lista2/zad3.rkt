#lang racket

(define-struct matrix (a b c d) #:transparent)          ;[a b]
                                                        ;[c d]
(define (matrix-mult m n)
    (make-matrix
    (+ (* (matrix-a m) (matrix-a n)) (* (matrix-b m) (matrix-c n)))     ;aa + bc  
    (+ (* (matrix-a m) (matrix-b n)) (* (matrix-b m) (matrix-d n)))     ;ab + bd
    (+ (* (matrix-c m) (matrix-a n)) (* (matrix-d m) (matrix-c n)))     ;ca + cd
    (+ (* (matrix-c m) (matrix-b n)) (* (matrix-d m) (matrix-d n)))     ;cb + dd
    ))

(define (matrix-id)             ;[1 0]
    (make-matrix 1 0 0 1))      ;[0 1]

(define (matrix-expt m k)
    (define (it input acc n)
        (if (= n 0) acc
            (it input (matrix-mult acc input) (- n 1))))

    (it m (make-matrix 1 1 1 1) k))
                                                     
(define (fib-matrix k)                          ;[1 1]^k    -> [Fk+1  Fk ]
    (matrix-expt (make-matrix 1 1 1 0) k))      ;[1 0]         [ Fk  Fk-1]

(matrix-b (fib-matrix 10))