#lang racket

(define (specialIf ifCond ifTrue ifFalse)
    (or (and ifCond ifTrue) ifFalse)
)

(specialIf (= 4 (* 2 2)) "True" "False")