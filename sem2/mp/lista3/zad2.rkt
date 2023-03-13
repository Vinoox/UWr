#lang racket

(define (my-foldl f x xs)
    (define (it xs acc)
        (if (null? xs) acc
            (it (cdr xs) (f (car xs) acc))
        )
    )

    (it xs x)
)

(define (product xs)
    (if (null? xs) 1    ;zwraca 1 dla pustej listy (element neutralny dla mnozenia)
        (my-foldl * (car xs) (cdr xs))
    )
)

(product (list 2 3 4 5))
(product (list))
(product (list 5))