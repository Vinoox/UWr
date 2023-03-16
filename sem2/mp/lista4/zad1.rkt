#lang racket

(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)

#|ZAD1
Rozważ drzewa binarne z wykładu. Narysuj, jak w pamięci reprezentowane jest
drzewo t zdefiniowane poniżej
|#

(define t
    (node
        (node (leaf) 2 (leaf))
        5
        (node (node (leaf) 6 (leaf))
            8
            (node (leaf) 9 (leaf)))))

#|
           5
        /     \
       2        8
      / \     /    \
     () ()   6      9
            / \     / \
           () ()   () ()
|#

#| dodanie 7

           5
        /      \
      2           8
     / \        /    \
    () ()      6      9
              / \     / \
             ()  7   () ()
                / \
               () ()
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

t
(define x (insert-bst 8 t))
x