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
    (my-foldl * 1 xs)
)

(product (list 2 3 4 5))
(product (list))
(product (list 5))