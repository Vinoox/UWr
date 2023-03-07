#lang racket

;Zadanie 9.

(define (rmv x xs)
   (if (null? xs) xs
      (if (= x (car xs)) (rmv x (cdr xs))
        (cons (car xs) (rmv x (cdr xs))))))

(define (minimum l)
   (define (itr x l)
      (if (null?  l)
         x
         (if (< x (car l))
            (itr x (cdr l))
            (itr (car l) (cdr l)))))
   (itr +inf.0 l))

(define (select xs)
   (define min (minimum xs))
        (cons min (rmv min xs)
    )
)

(define (selection-sort xs)
   (if (null? xs)
     xs
      (cons (car (select xs)) (selection-sort (cdr (select xs))))))