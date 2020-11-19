#lang racket

(require "zip-install.rkt")

(define $cwd (current-directory))

(define $home-dir (find-system-path 'home-dir))
$home-dir

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

(copy-file (format "~a\\.emacs" $cwd) (format "~a\\.emacs" $unix-home) #t)
(copy-file (format "~a\\c-quick-2.el" $cwd) (format "~a\\c-quick-2.el" $unix-home) #t)

;(set-registry-env! "USER" "MSYSTEM" "MINGW64")
;(set-registry-env! "USER" "MSYSTEM_CARCH" "x86_64")
;(set-registry-env! "USER" "MSYSTEM_CHOST" "x86_64-w64-mingw32")

;(define $usr-bin (format "~a\\usr\\bin" $target-dir))
;(define $mingw64r-bin (format "~a\\mingw64\\bin" $target-dir))
;(new set-path% [:member $usr-bin])
;(new set-path% [:member $mingw64r-bin])
(new set-path% [:member $target-dir])
