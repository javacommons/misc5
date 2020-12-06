#! racket
#lang racket
(provide rectangle%)

(define rectangle%
  (class object% (super-new)
    (init-field width)
    (init-field height)
    (define (set-width n) (set! width n))
    (define (get-width) width)
    (define (area) (* height width))
    (public set-width get-width area)
    )
  )

(define rectangle-ex%
  (class rectangle% (super-new)
    (init-field (bonus 0))
    (define/override (area) (+ (super area) bonus))
    )
  )

(define rect1 (new rectangle-ex% (width 10) (height 20) (bonus 23)))
(send rect1 area)
