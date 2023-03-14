#lang racket

#|ZAD4
Złożenie funkcji f i g definiujemy (jak pamiętamy z przedmiotu „Logika dla informatyków”) jako funkcję x → f(g(x)).
Zdefiniuj dwuargumentową procedurę my-compose, której wynikiem jest złożenie (jednoargumentowych) procedur przekazanych jej jako argumenty. 
Używając modelu podstawieniowego, prześledźwykonanie wyrażeń|#

(define (square x)
    (* x x)
)

(define (inc x)
    (+ x 1)
)

(define (my-compose f g)
    (lambda (x) (f (g x)))
)

((my-compose square inc) 5)
#|
    (( my-compose square inc ) 5) -> [(lambda (x) (square (inc x))) 5]
    x = 5
    (square (inc 5))
    (inc 5) -> 6
    (square 6) -> 36
|#


((my-compose inc square) 5)
#|
    (( my-compose inc square ) 5) -> [(lambda (x) (inc (square x))) 5]
    x = 5
    (inc (square 5))
    (square 5) -> 25
    (inc 25) -> 26 
|#