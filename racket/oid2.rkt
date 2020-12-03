#! racket
#lang racket

(require "../mylib/mylib-oid.rkt")

(to-oid 'a)
(to-oid 'b)
(to-oid 'a)
(define $list (list 11 22 33))
(define $list2 (list 11 22 33))
(to-oid $list)
(to-oid $list2)
(to-oid $list)

(from-oid 3)

(to-oid (void))

(printf "count-1=~s\n" (oid-count))
(set! $list (void))
(set! $list2 (void))
(collect-garbage)
(printf "count-2=~s\n" (oid-count))
(eq? $list $list2)

(define $th (current-thread))
(to-oid $th)
(define $n1 18446744073709551615)
(define $n2 18446744073709551615)
(eq? $n1 $n2)

(for/list ([$i (list 11 22 33)]) (to-oid $i))
