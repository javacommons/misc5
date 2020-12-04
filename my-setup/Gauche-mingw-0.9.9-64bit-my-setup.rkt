#! racket64
#lang racket

(require "../mylib/mylib-zip-install.rkt")

(define $cwd (current-directory))

(define $home-dir (find-system-path 'home-dir))
$home-dir

(set! $home-dir (simplify-path (build-path $home-dir 'up "Public")))
$home-dir

;(define $run-file-dir (run-file-dir))
;$run-file-dir

(define $pd (new prepare-dir%
		 [:root-dir $home-dir]
		 [:zip-base "Gauche-mingw-0.9.9-64bit"]
     ))

(define $target-dir (send $pd :get-target-dir))
$target-dir

(new set-path% [:member (build-path $target-dir "bin")])

(new fix-path%)
