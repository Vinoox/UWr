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


(define (fold-tree f tree)
    (if (and (leaf? node-l) (leaf? node-r)) node-l
        (cond
            [(leaf? node-l) (f (leaf) (fold-tree f node-r))]
            [(leaf? node-r) (f (fold-tree f node-l) (leaf))]
            [else (f (fold-tree f node-l) (fold-tree f node-r))]
        )
    )
)

(leaf? node-l)

(define (tree-sum t)
    (fold-tree + t)
)

(tree-sum t)

(define tree-flip t)
(define tree-height t)
(define tree-span t)
(define flatten t)