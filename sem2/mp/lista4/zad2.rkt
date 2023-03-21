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

#|ZAD 2
    Tak jak najprostszy schemat rekursji na listach można wyabstrahować do procedury foldr, 
    tak najprostszy schemat rekursji na drzewach z wykładu można
    wyabstrahować do procedury fold-tree. Zdefiniuj tę procedurę i wyraź przy
    jej użyciu procedury:
|#

#|(define (my-foldr f x xs)
  (if (null? xs)
      x
      (f (car xs) (my-foldr f x (cdr xs)))))|#

(define (fold-tree f acc tree)
    (if (leaf? tree) acc
        [f  (fold-tree f acc (node-l tree))  (node-elem tree)  (fold-tree f acc (node-r tree))]
    )
)

;(tree-sum t) – suma wszystkich wartości występujących w drzewie

(define (tree-sum tree)
    (fold-tree 
        +  ;f
        0  ;acc
        tree)   ;tree
)
(tree-sum t)


;(tree-flip t) – odwrócenie kolejności: zamiana lewego i prawego poddrzewa wszystkich węzłów w drzewie

(define (tree-flip tree)
    (fold-tree 
        (lambda (l elem r) (make-node r elem l)) ;f
        (leaf)  ;acc
        tree    ;tree
    )
)
(tree-flip t)


;(tree-height t) – wysokosć drzewa (liczba węzłów na najdłuższej ścieżce od korzenia do liścia)

(define (tree-height tree)
    (fold-tree 
        (lambda (l elem r) (+ (max l r) 1)) ;f
        0       ;acc
        tree    ;tree
    )
)
(tree-height t)


;(tree-span t) – para złożona z wartości skrajnie prawego i skrajnie lewego węzła w drzewie 
;(czyli najmniejszej i największej wartości w drzewie BST)

(define (tree-span tree)
    (fold-tree 
        (lambda (l elem r) [cons (min elem (car l)) (max elem (cdr r))] ) ;f
        (cons +inf.0 -inf.0)    ;acc
        tree ;tree
    )
)
(tree-span t)


;(flatten t) – lista wszystkich elementów występujących w drzewie, w kolejności infksowej

(define (flatten tree)
    (fold-tree 
        (lambda (l elem r) (append l (cons elem r))) ;f
        (list)  ;acc
        tree    ;tree
    )
)

(flatten t)