#lang racket

;Zadanie 8.
;Zaimplementuj procedurę (sorted? xs) sprawdzającą, czy zadana lista jest
;posortowana niemalejąco.

(define (sorted? xs)
    (define (it x xs)
        (cond 
            [(null? xs) #t]
            [(> x (car xs)) #f]
            [else (it (car xs) (cdr xs))]
        )
    )

    (it -inf.0 xs)
)

(sorted? (list 1 2 3 4 5))
(sorted? (list 1 3 2 4 5))