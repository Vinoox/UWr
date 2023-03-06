#lang racket

(define (elem? x xs)
    (cond
        [(null? xs) #f]
        [(equal? x (car xs)) #t]
        [else (elem? x (cdr xs))]
    )
)

(elem? 8 (list 1 2 3 4 5))
(elem? 5 (list 1 2 3 4 5))