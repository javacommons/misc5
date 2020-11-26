#! racket32
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
    (field [%:width :width])
    (field [%:height :height])
    (define/public (:get-width) %:width)
    (define/public (:set-width %n) (set! %:width %n))
    (define/public (:area) (* %:width %:height))
    )
  )

(define subclass%
  (class
    rectangle% (init :width :height [:bonus 0])
    (super-new [:width :width] [:height :height])
    (inherit-field %:width)
    (inherit-field %:height)
    (field [%:bonus :bonus])
    (println %:bonus)
    ;(inherit [:get-width :my-get-width])
    (inherit [:my-get-width :get-width])
    ;(inherit :set-width)
    ;(define/public (:test) %:width)
    (define/public (:test) (:my-get-width))
    (define/override (:area)
      (+ (super :area) %:bonus)
      )
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

(define $subclass (new subclass% [:width 10] [:height 20] [:bonus 12]))
(send $subclass :test)
(send $subclass :area)
(send $subclass :set-width 15)
(send $subclass :area)
;(read-line)

(define calc0%
  (class object% (super-new)
    (define/public (:add2 %x %y) (+ %x %y))
    )
  )

(define $c0 (new calc0%))
(send $c0 :add2 11 22)

(define calc1%
  (class calc0% (super-new)
    (define/override (:add2 %x %y) (* (super :add2 %x %y) 10))
    )
  )

(define $c1 (new calc1%))
(send $c1 :add2 11 22)
