#lang racket

#|ZAD2
Wzorując się na procedurze z wykładu sumującej liczby przy użyciu foldl, zdefi-
niuj procedurę product, obliczającą iloczyn elementów listy. 
Jaką wartość powinien zwracać product dla listy pustej?|#

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



#|
(define (product xs)
    (if (null? xs) 0
        (my-foldl  * (car xs) (cdr xs))
    )
)
|#