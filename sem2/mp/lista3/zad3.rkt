#lang racket

#|ZAD3
Używając modelu podstawieniowego, prześledź wykonanie wyrażeń|#

((lambda (x y) (+ x (* x y))) 1 2)
#|
    x = 1, y = 2
    (+ 1 (* 1 2))
    (+ 1 2)
    3
|#


((lambda (x) x) (lambda (x) x))
#|
    x = (lambda (x) x)
    (lambda (x) x)  <- procedura
|#


((lambda (x) (x x)) (lambda (x) x))
#|
    x = (lambda (x) x)
    ((lambda (x) x) (lambda (x) x)) <- przyklad 2
    x = (lambda (x) x)
    (lambda (x) x) <- procedura
|#


((lambda (x) (x x)) (lambda (x) (x x)))
#|
    x = (lambda (x) (x x))
    ((lambda (x) (x x)) (lambda (x) (x x)))

    x = (lambda (x) (x x))
    ((lambda (x) (x x)) (lambda (x) (x x)))
    
    x = (lambda (x) (x x))
    ...
    ZAPETLENIE
|#