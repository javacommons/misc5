#! racket
#lang racket
(provide rectangle%)

(define rectangle%
  (class object% (init width height) (super-new)
    (field [f-width width]
           [f-height height])
    (define (set-width n) (set! f-width n))
    (define (get-width) f-width)
    (define (set-height n) (set! f-height n))
    (define (get-height) f-height)
    (define (area) (* f-height f-width))
    (public set-width get-width area)
    )
  )
