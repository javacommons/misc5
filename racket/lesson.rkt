#lang racket

; https://learnxinyminutes.com/docs/racket/

#| Block comments
   can span multiple lines and...
    #|
       they can be nested!
    |#
|#

#; (this expression is discarded)

(println "hello")

18446744073709551615
18446744073709551615777
(require json)
(jsexpr->string 18446744073709551615777)

#;(error "my-error")

(/ 1 3) ; => 1/3
(exact->inexact 1/3) ; => 0.3333333333333333
(+ 1+2i  2-3i) ; => 3-1i

;; Strings can be added too!
(string-append "Hello " "world!") ; => "Hello world!"

;; A string can be treated like a list of characters
(string-ref "Apple" 0) ; => #\A

;; format can be used to format strings:
(format "~a can be ~a" "strings" "formatted")

;; Printing is pretty easy
(printf "I'm Racket. Nice to meet you!\n")

;; You can also use unicode characters
(define ⊆ subset?)
(⊆ (set 3 2) (set 1 2 3)) ; => #t

(define rectangle%
  (class
   object% (super-new)
   (init :width :height)
   (define $width :width)
   (define $height :height)
   (define/public (:get-width) $width)
   (define/public (:set-width %n) (set! $width %n))
   (define/public (:area) (* $width $height))
   )
  )

(define $rect (new rectangle% [:width 15] [:height 20]))
(send $rect :get-width)
(send $rect :area)
(send $rect :set-width 5)
(send $rect :area)

(define (square %n #:bonus [%bonus 0]) (+ (* %n %n) %bonus))
(square 100)
(square 100 #:bonus 123)
(square #:bonus 4567 100)

(define (test %x #:bonus %bonus)
  (println %x)
  (println %bonus)
  )

(test 123 #:bonus 456)

(require json)

(define n (/ 1 3))
n

(jsexpr->string (exact->inexact n))

(/ 1.0 3.0)
(exact->inexact 0.2)
