#! racket
#lang racket
; https://stackoverflow.com/questions/56386674/unique-identifier-for-racket-objects

(provide to-oid from-oid oid-count)

(define $oid-ht (make-weak-hasheq))
(define $oid-reverse-ht (make-hasheq))
(define $oid-next 0)
(define $oid-semaphore (make-semaphore 1))

(define (to-oid %x)
  (call-with-semaphore
   $oid-semaphore
   (lambda ()
     (define %oid (hash-ref $oid-ht %x #f))
     (or %oid
         (begin0
           $oid-next
           (hash-set! $oid-ht %x $oid-next)
           (hash-set! $oid-reverse-ht $oid-next (make-weak-box %x))
           (set! $oid-next (+ $oid-next 1)))))))

(void (to-oid #f))

(define (from-oid %oid)
  (call-with-semaphore
   $oid-semaphore
   (lambda ()
     (define %box (hash-ref $oid-reverse-ht %oid #f))
     (and %box
          (weak-box-value %box)))))

(define (oid-count)
  (hash-count $oid-ht))

;;;;; test ;;;;;

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
