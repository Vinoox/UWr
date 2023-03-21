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

#|ZAD 5
    Zmodyfikuj procedurę insert z wykładu (wstawiającą element do drzewa BST)
    tak, aby możliwe było tworzenie drzew BST z duplikatami. Możesz założyć,
    że elementy równe elementowi w korzeniu drzewa będą trafiać do prawego
    poddrzewa
|#

(define (insert-bst x t)
  (cond [(leaf? t) (node (leaf) x (leaf))]
        [(node? t)
            (cond [(= x (node-elem t)) t]
                [(< x (node-elem t))
                 (node (insert-bst x (node-l t))
                       (node-elem t)
                       (node-r t))]
                [else
                 (node (node-l t)
                       (node-elem t)
                       (insert-bst x (node-r t)))])]))

(define (insert-bstv2 x t)
  (cond [(leaf? t) (node (leaf) x (leaf))]
        [(node? t)
            (if (< x (node-elem t))
                (node 
                    (insert-bstv2 x (node-l t))
                    (node-elem t)
                    (node-r t))

                (node 
                    (node-l t)    
                    (node-elem t)
                    (insert-bstv2 x (node-r t))))]))

(insert-bst 5 t)
(insert-bstv2 5 t)

#|
    Zaimplementuj procedurę (treesort xs), implementującą algorytm sortowania przy użyciu drzew BST:
    • Utwórz drzewo przeszukiwania składające się z elementów listy xs.
    • Zwróć listę elementów drzewa w kolejności infiksowej
|#

;procedury z zad 2
(define (fold-tree f acc tree)
    (if (leaf? tree) acc
        [f  (fold-tree f acc (node-l tree))  (node-elem tree)  (fold-tree f acc (node-r tree))]
    )
)

(define (flatten tree)
    (fold-tree 
        (lambda (l elem r) (append l (cons elem r))) ;f
        (list)  ;acc
        tree    ;tree
    )
)

(define (treesort xs)
    (define (itr xs)
        (if (null? (cdr xs)) (insert-bstv2 (car xs) (leaf))
            (insert-bstv2 (car xs) (itr (cdr xs)))
        )
    )

    (flatten (itr xs))
)

(define xs (list 7 8 1 4 2 7 5))

(treesort xs)