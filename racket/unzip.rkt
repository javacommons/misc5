#! racket32
#lang racket

(require file/unzip)

(define $void (void))
(define $file-in (open-input-file "msys64.zip" #:mode 'binary))
(define $zipdir (read-zip-directory $file-in))
(define $entries (zip-directory-entries $zipdir))
(current-directory "zip.tmp")
(set! $void (for/list ([$entry $entries])
  (println $entry)
  (unzip-entry $file-in $zipdir $entry #:preserve-timestamps? #t)))
