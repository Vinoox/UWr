#lang racket

;Zadanie 6.
;Zaimplementuj procedurę (maximum xs) znajdującą największy element na
;liście (względem predykatu >). Jeśli lista xs pusta, zwracana jest wartość -inf.0 (minus nieskończoność). 

(define (maximum xs)
    (define (it x xs)
        (cond
            [(null? xs) x]
            [(> x (car xs)) (it x (cdr xs))]
            [else (it (car xs) (cdr xs))]
        )            
    )
    
    (it -inf.0 xs)
)

(maximum (list 6 2 5 9 4))
(maximum (list))