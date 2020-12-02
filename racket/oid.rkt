#lang racket
; https://stackoverflow.com/questions/56386674/unique-identifier-for-racket-objects


(require ffi/unsafe)

(define (madness v) ; i'm so sorry
  (cast v _racket _gcpointer))


(define a (list 1 2))
(define b (list 1 2))

(printf "a and b have different address: ~a ~a\n"
        (equal? (madness a) (madness b))
        (eq? a b))

(printf "a and a have the same address: ~a ~a\n"
        (equal? (madness a) (madness a))
        (eq? a a))

(printf "1 and 1 have the same address: ~a ~a\n"
        (equal? (madness 1) (madness 1))
        (eq? 1 1))

(define $m (madness (list 1 2)))
$m
(cond
  [(= (system-type 'word) 32)
   (cast $m _gcpointer _uint32)]
  [(= (system-type 'word) 64)
   (cast $m _gcpointer _uint64)])

(define (oid %x)
  (define %p (cast %x _racket _gcpointer))
  (cond
    [(= (system-type 'word) 32)
     (cast %p _gcpointer _uint32)]
    [(= (system-type 'word) 64)
     (cast %p _gcpointer _uint64)]
    [else -1]))

(oid (list 1 2))
