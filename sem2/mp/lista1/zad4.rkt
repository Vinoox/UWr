#lang racket

(require rackunit)

(define (square num)
    (* num num))

(define (task num1 num2 num3)
    (cond [(and (> num1 num3) (> num2 num3)) (+ (square num1) (square num2))]
        [(and (> num1 num2) (> num3 num2)) (+ (square num1) (square num3))]
        [else (+ (square num2) (square num3))]))

(check-equal? (task 20 22 42) 2248 "test1")
(check-equal? (task 3 1 2) 13 "test2")
(check-equal? (task 10 10 10) 200 "test3")