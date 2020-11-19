#lang racket

(require "zip-install.rkt")

;(define $home-dir (find-system-path 'home-dir))
;(define $home-dir "C:\\Users\\Public")
(define $home-dir "C:\\")
$home-dir

(define $pd (new prepare-dir%
		 [:root-dir $home-dir]
		 [:zip-base "racket-7.9-64bit"]
     ))

(define $target-dir (send $pd result))
$target-dir

(new set-path% [:member $target-dir])
