#lang racket

;Zadanie 7.
;Zaimplementuj procedurę (suffixes xs) zwracającą wszystkie sufksy listy
;xs – czyli takie listy, które zawierają, w kolejności i bez powtórzeń, elementy
;listy xs od zadanego elementu aż do końca listy. Listę pustą uznajemy za sufks
;dowolnej listy

(define (suffixes xs)
   (if (null? xs) (cons xs null)  
      (cons xs (suffixes (cdr xs)))))

(suffixes (list 4 7 1 9))

;(suf [4 7 1 9])
;A.(cons [4 7 1 9] (s [7 1 9]))
;B. (cons [7 1 9] (s [1 9]))
;C. (cons [1 9] (s [9]))
;D. (cons [9] [])

;C. (cons [1 9] [ [9] [] ])
;B. (cons [7 1 9] [ [1 9] [9] [] ])
;A. (cons [4 7 1 9] [ [7 1 9] [1 9] [9] [] ])

;[ [4 7 1 9] [7 1 9] [1 9] [9] [0]]