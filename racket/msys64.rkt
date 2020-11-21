#! racket32
#lang racket

(require "zip-install.rkt")

(define $cwd (current-directory))

(define $home-dir (find-system-path 'home-dir))
$home-dir

;(define $run-file (simplify-path (path->complete-path (find-system-path 'run-file))))
;$run-file

;(define $run-dir (path->complete-path (build-path $run-file 'up)))
;$run-dir

;(println "[temp]")
;(define-values (%base %name %must-be-dir?) (split-path $run-file))
;%base

(define $run-file-dir (run-file-dir))
$run-file-dir

;(path->directory-path $run-file)

;(find-executable-path $run-file)

;(exit)

(define $pd (new prepare-dir%
		 [:root-dir $home-dir]
		 [:zip-base "msys64"]
     ))

(define $target-dir (send $pd :get-target-dir))
$target-dir

(define $user (getenv "USERNAME"))
(define $unix-home (format "~a\\home\\~a" $target-dir $user))
$unix-home
(make-directory* $unix-home)
;(set-registry-env! "USER" "HOME" $unix-home)

(copy-file (format "~a\\.bashrc" $run-file-dir) (format "~a\\.bashrc" $unix-home) #t)
(copy-file (format "~a\\.emacs" $run-file-dir) (format "~a\\.emacs" $unix-home) #t)
(copy-file (format "~a\\c-quick-2.el" $run-file-dir) (format "~a\\c-quick-2.el" $unix-home) #t)

(new set-path% [:member $target-dir])
