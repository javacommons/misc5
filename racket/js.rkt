#! racket32
#lang racket

(define hooclass%
  (class object% (init :z) (super-new)
    (field [%:z :z])
    (define (:get-z) %:z)
    (define (:set-z %z) (set! %:z %z))
    (public :get-z :set-z)
    )
  )

(define $hoo (new hooclass% [:z 20]))
(send $hoo :get-z)

(define taaclass%
  (class hooclass% (init :z :num) (super-new [:z :z])
    (inherit-field %:z)
    (field [%:num :num])
    (define (:calc) (* %:z %:num))
    (public :calc)
    )
  )

(define $taa (new taaclass% [:z 20] [:num 3]))
(println (send $taa :calc))
(send $taa :set-z 100)
(println (send $taa :calc))

(define test1%
  (class object% (init) (super-new)
    (define (:sub1) 123)
    (field [%:f1 (:sub1)])
    (public [:sub1 :psub1])
    )
  )

(define $test1 (new test1%))
$test1
(send $test1 :psub1)

