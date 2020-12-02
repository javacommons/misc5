#lang racket

(require "rectangle.rkt")

(define rectangle-ex%
  (class rectangle% (init width height [bonus 0])
    (super-new [width width] [height height])
    (field [f-bonus bonus])
    (define/override (area) (+ (super area) f-bonus))
    )
  )
 
(define $rect1 (new rectangle-ex%
                    [height 10]
                    [width 15]
                    [bonus 23]))
(send $rect1 area)
