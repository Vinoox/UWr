#lang racket

;Zadanie 5.
;Zaimplementuj procedurę (elem? x xs) sprawdzającą, czy element x znajduje
;się na liście xs (użyj predykatu equal?)

(define (elem? x xs)
    (cond
        [(null? xs) #f]
        [(equal? x (car xs)) #t]
        [else (elem? x (cdr xs))]
    )
)

(elem? 8 (list 1 2 3 4 5))
(elem? 5 (list 1 2 3 4 5))