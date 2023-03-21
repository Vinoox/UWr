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

#|ZAD 3 
    Zaimplementuj następujące procedury:
|#


#|
    (bst? t) – predykat sprawdzający, czy zadane drzewo spełnia własność
    BST. Zadbaj o to, aby każdy wierzchołek drzewa odwiedzić tylko raz
|#

(define (fold-tree f acc tree)
    (if (leaf? tree) acc
        [f  (fold-tree f acc (node-l tree))  (node-elem tree)  (fold-tree f acc (node-r tree))]
    )
)

(define (bst? tree)
    (fold-tree
        (lambda (l elem r) 
            (cond
                [(= #t l r) #t]
                [(= #t l) (if (elem <= (node-elem r)) #t #f)]
                [(= #t r) (if (elem < (node-elem l)) #t #f)]
                [(or (= #f l) (= #f r)) #f]
                [else (if (and (elem <= (node-elem r)) (elem < (node-elem l))) #t #f)]
            )
        )
        (+inf.0 -inf.0)
        tree
    )
)

(bst? t)