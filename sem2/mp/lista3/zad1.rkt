#lang racket

#|ZAD1
Zapisz poniższe wyrażenia w równoważnej postaci tak, by znak cytowania
występował jedynie w podwyrażeniach reprezentujących symbole. Nie obliczaj
żadnych podwyrażeń! Możesz użyć procedur list i cons.|#

;1
'(( car ( a . b ) ) (* 2))

(list '(car (a . b)) '(* 2))

;2
`( ,( car '( a . b ) ) ,(* 2) )

(list (car '(a . b)) (* 2))

;3
'((+ 1 2 3) (cons) (cons a b))

(list '(+ 1 2 3) '(cons) '(cons a b))