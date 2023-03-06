#lang racket

;Zadanie 1.
;W poniższych wyrażeniach zlokalizuj wolne i związane wystąpienia zmiennych.
;Które wystąpienia wiążą każde z wystąpień związanych?

( let ([x 3])
    (+ x y ) )     ;x - zmienna zwiazana, y - zmienna wolna


( let ([x 1]
    [ y (+ x 2) ])  ;x- zmienna wolna w (+ x 2)
    (+ x y ) )      ;x, y - zmienna zwiazana


( let ([x 1])
    ( let ([ y (+ x 2) ])  ;x - zmienna zwiazana
        (* x y ) ) )       ;x,y - zmienne zwiazane


( define (f x y)
    (* x y z ) )    ;x, y - zmienne zwiazane, z - zmienna wolna


( define (f2 x)
    ( define (g y z)
        (* x y z ) )    ;x - zmienna wolna, y, z - zmienna zwiazana
    ( f2 x x x ) )      ;x - zmienna zwiazana