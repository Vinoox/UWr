#lang racket

(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)

(define t
    (node
        (node (leaf) 2 (leaf))
        5
        (node (node (leaf) 6 (leaf))
            8
            (node (leaf) 9 (leaf)))))


(define (fold-tree f startValue tree)
    (cond
        [(and (leaf? (node-l tree)) (leaf? (node-r tree))) (node-elem tree)]
        [(leaf? (node-l tree)) (f startValue (fold-tree f startValue (node-r tree)))]
        [(leaf? (node-r tree)) (f (fold-tree f startValue (node-l tree)) startValue)]
        [else (f (node-elem tree) (fold-tree f startValue (node-l tree)) (fold-tree f startValue (node-r tree)))]
    )
)


(define (tree-sum t)
    (fold-tree + 0 t)
)

(tree-sum t)

(define (tree-flip t)
    (t)
)


(define tree-height t)
(define tree-span t)
(define flatten t)