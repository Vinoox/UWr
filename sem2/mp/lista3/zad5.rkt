#lang racket

(define (bulid-list n f)
   (define (it x f)
      (if (= x n) (list)
         (cons (f x) (it (+ x 1) f))
      )
   )
   (it 0 f)
)

;#1
(define negate
   (lambda (x) (- (+ x 1)))
)

(define (negatives n)
   (bulid-list n negate)
)

(negatives 10)


;#2
(define divide
   (lambda (x) (/ 1 (+ x 1)))
)

(define (reciprocals n)
   (bulid-list n divide)
)

(reciprocals 10)


;#3
(define double
   (lambda (x) (* x 2))
)

(define (evens n)
   (bulid-list n double)
)

(evens 10)


#|4               
[[1 0 0 0]
 [0 1 0 0]
 [0 0 1 0]
 [0 0 0 1]]
|#

(define (identityM n)
   (define (helper i j)
      (if (= j i) 1 0)
   )

   (bulid-list n (lambda (i) (bulid-list n (lambda (j) (helper i j)))))
)

(identityM 3)