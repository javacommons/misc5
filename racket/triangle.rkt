#! racket32
#lang racket
(require 2htdp/image)
(define $image
  (let sierpinski ([n 8])
    (if (zero? n)
        (triangle 2 'solid 'red)
        (let ([t (sierpinski (- n 1))])
          (freeze (above t (beside t t)))))))
(save-image $image "tri.png")
; https://ja.wikipedia.org/wiki/Racket
; https://docs.racket-lang.org/teachpack/2htdpimage.html